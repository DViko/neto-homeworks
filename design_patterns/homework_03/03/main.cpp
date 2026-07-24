#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

enum class Type
{
    Warning,
    Error,
    Fatal,
    Unknown
};

class LogMessage
{
    private:

        Type type_;
        std::string message_;

    public:

        LogMessage(Type type, std::string message)
                    : type_(type), message_(std::move(message))
        {
        }

        Type type() const
        {
            return type_;
        }

        const std::string& message() const
        {
            return message_;
        }
};

class Handler
{
    protected:

        Handler* next_ = nullptr;

    public:

        virtual ~Handler() noexcept = default;

        void set_next(Handler* next)
        {
            next_ = next;
        }

        virtual void handle(const LogMessage& message) = 0;
};

class WarningHandler : public Handler
{
public:

    void handle(const LogMessage& message) override
    {
        if (message.type() == Type::Warning)
        {
            std::cout << "Warning: " << message.message() << '\n';
        }
        else if (next_)
        {
            next_->handle(message);
        }
    }
};

class ErrorHandler : public Handler
{
    private:

        std::filesystem::path path_;

    public:

        explicit ErrorHandler(std::filesystem::path path) : path_(std::move(path))
        {
        }

        void handle(const LogMessage& message) override
        {
            if (message.type() == Type::Error)
            {
                std::ofstream file(path_, std::ios::app);

                if (!file)
                {
                    throw std::runtime_error("Error: Cannot open file.");
                }

                file << message.message() << '\n';
            }
            else if (next_)
            {
                next_->handle(message);
            }
        }
};

class FatalHandler : public Handler
{
public:

    void handle(const LogMessage& message) override
    {
        if (message.type() == Type::Fatal)
        {
            throw std::runtime_error("Fatal error: " + message.message());
        }

        if (next_)
        {
            next_->handle(message);
        }
    }
};

class UnknownHandler : public Handler
{
public:

    void handle(const LogMessage& message) override
    {
        if (message.type() == Type::Unknown)
        {
            throw std::runtime_error("Unhandled message: " + message.message());
        }
    }
};


int main()
{
    FatalHandler fatal;
    ErrorHandler error("error.log");
    WarningHandler warning;
    UnknownHandler unknown;

    fatal.set_next(&error);
    error.set_next(&warning);
    warning.set_next(&unknown);


    fatal.handle(LogMessage(Type::Warning, "Low memory"));

    fatal.handle(LogMessage(Type::Error, "Cannot open config")); // Check error.log

    try
    {
        fatal.handle(LogMessage(Type::Fatal, "Database lost"));
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }

    try
    {
        fatal.handle(LogMessage(Type::Unknown, "Unexpected message"));
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << '\n';
    }

    return 0;
}
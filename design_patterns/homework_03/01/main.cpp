#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>


class Logger;

class ICommand
{
    public:

        virtual ~ICommand() = default;
        virtual void execute() const = 0;
};

class ConsoleLogCommand : public ICommand
{
    private:

        Logger& logger_;
        std::string message_;

    public:

        ConsoleLogCommand(Logger& logger, std::string message);

        void execute() const override;
};

class FileLogCommand : public ICommand
{
    private:

        Logger& logger_;
        std::filesystem::path path_;
        std::string message_;

    public:

        FileLogCommand(Logger& logger, std::filesystem::path path, std::string message);

        void execute() const override;
};


class Invoker
{
    private:

        std::vector<ICommand*> commands_;

    public:

        void add_command(ICommand& command)
        {
            commands_.push_back(&command);
        }

        void run(std::size_t index) const
        {
            if (index < commands_.size())
            {
                commands_[index]->execute();
            }
        }
};

class Logger
{
    public:

        void write_console(const std::string& message) const
        {
            std::cout << message << '\n';
        }

        void write_file(const std::filesystem::path& path, const std::string& message) const
        {
            std::ofstream file(path, std::ios::app);

            if (file)
            {
                file << message << '\n';
            }
        }
};


ConsoleLogCommand::ConsoleLogCommand(Logger& logger, std::string message)
                                      : logger_(logger), message_(std::move(message))
{
}

void ConsoleLogCommand::execute() const
{
    logger_.write_console(message_);
}


FileLogCommand::FileLogCommand(Logger& logger, std::filesystem::path path, std::string message)
                                 : logger_(logger), path_(std::move(path)), message_(std::move(message))
{
}

void FileLogCommand::execute() const
{
    logger_.write_file(path_, message_);
}


int main()
{
    Logger logger;

    ConsoleLogCommand console(logger, "Hello Console!");
    FileLogCommand file(logger, "log.txt", "Hello File!");

    Invoker invoker;

    invoker.add_command(console);
    invoker.add_command(file);

    invoker.run(0);
    invoker.run(1);

    return 0;
}
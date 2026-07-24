#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Observer
{
    public:

        virtual ~Observer() = default;

        virtual void on_warning(const std::string& message)
        {
        }

        virtual void on_error(const std::string& message)
        {
        }

        virtual void on_fatal_error(const std::string& message)
        {
        }
};

/*
 * Note:
 *
 * The Observer base class intentionally provides default implementations
 * for all event handlers instead of declaring them as pure virtual functions.
 *
 * The interface exposes callbacks for all event types, although each
 * concrete observer typically overrides only the callbacks it requires.
 * 
 * As a result, this design does not strictly comply with the Interface Segregation Principle (ISP).
 */


class Observable
{
    private:

        using Callback = void (Observer::*)(const std::string&);

        std::vector<std::weak_ptr<Observer>> observers_;

    private:

        void cleanup()
        {
            observers_.erase(std::remove_if(observers_.begin(), observers_.end(), [](const auto& observer)
            {
                return observer.expired();
            }),
            observers_.end());
        }

        void dispatch(Callback callback, const std::string& message)
        {
            cleanup();

            for (const auto& observer : observers_)
            {
                if (auto ptr = observer.lock())
                {
                    (ptr.get()->*callback)(message);
                }
            }
        }

public:

    void add_observer(const std::shared_ptr<Observer>& observer)
    {
        observers_.push_back(observer);
    }

    void remove_observer(const std::shared_ptr<Observer>& observer)
    {
        observers_.erase(std::remove_if(observers_.begin(), observers_.end(), [&](const auto& weak)
        {
            return weak.expired() || weak.lock() == observer;
        }),
        observers_.end());
    }

    void warning(const std::string& message)
    {
        dispatch(&Observer::on_warning, message);
    }

    void error(const std::string& message)
    {
        dispatch(&Observer::on_error, message);
    }

    void fatal_error(const std::string& message)
    {
        dispatch(&Observer::on_fatal_error, message);
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

            if (!file)
            {
                throw std::runtime_error("Cannot open file.");
            }

            file << message << '\n';
        }
};

class WarningObserver : public Observer
{
    private:

        Logger& logger_;

    public:

        explicit WarningObserver(Logger& logger) : logger_(logger)
        {
        }

        void on_warning(const std::string& message) override
        {
            logger_.write_console(message);
        }
};

class ErrorObserver : public Observer
{
    private:

        Logger& logger_;
        std::filesystem::path path_;

    public:

        ErrorObserver(Logger& logger, std::filesystem::path path) : logger_(logger), path_(std::move(path))
        {
        }

        void on_error(const std::string& message) override
        {
            logger_.write_file(path_, message);
        }
};

class FatalErrorObserver : public Observer
{
    private:

        Logger& logger_;
        std::filesystem::path path_;

    public:

        FatalErrorObserver(Logger& logger, std::filesystem::path path) : logger_(logger), path_(std::move(path))
        {
        }

        void on_fatal_error(const std::string& message) override
        {
            logger_.write_console(message);
            logger_.write_file(path_, message);
        }
};

int main()
{
    Logger logger;

    Observable observable;

    auto warning = std::make_shared<WarningObserver>(logger);

    auto error = std::make_shared<ErrorObserver>(logger, "error.log");

    auto fatal = std::make_shared<FatalErrorObserver>(logger, "fatal.log");

    observable.add_observer(warning);
    observable.add_observer(error);
    observable.add_observer(fatal);

    observable.warning("Low memory.");
    observable.error("Cannot open configuration file.");
    observable.fatal_error("Database connection lost.");

    return 0;
}
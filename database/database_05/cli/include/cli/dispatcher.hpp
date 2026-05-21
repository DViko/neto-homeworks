#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace cli
{
    class CommandDispatcher
    {
        public:
            using Action = std::function<void()>;

            struct Command
            {
                std::string key;
                std::string description;
                Action action;
            };

            void register_command(Command command);
            bool dispatch(std::string key) const;

            const std::vector<Command>& commands() const;

        private:
            std::vector<Command> commands_;
            std::unordered_map<std::string, Action> actions_;
    };
}
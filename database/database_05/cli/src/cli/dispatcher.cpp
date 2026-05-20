#include "cli/dispatcher.hpp"

namespace cli
{
    void CommandDispatcher::register_command(Command command)
    {
        actions_.emplace(command.key, command.action);
        commands_.push_back(std::move(command));
    }

    bool CommandDispatcher::dispatch(std::string key) const
    {
        const auto it = actions_.find(key);

        if (it == actions_.end())
        {
            return false;
        }

        it->second();

        return true;
    }

    const std::vector<CommandDispatcher::Command>& CommandDispatcher::commands() const
    {
        return commands_;
    }
}
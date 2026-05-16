#pragma once

#include "contact.hpp"
#include "contact_repository.hpp"

#include <iostream>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace cli
{
    class ContactCLI
    {
        public:
            explicit ContactCLI(repositories::ContactRepository& repo);
            void run();

        private:
            bool m_running{true};
            repositories::ContactRepository& m_repo;
            using CommandHandler = std::function<void()>;

            struct CommandDefinition
            {
                std::string_view key;
                std::string_view description;
                CommandHandler action;
            };

            std::vector<CommandDefinition> m_command_definitions;

            void register_commands();
            void show_menu() const;

            void handle_create_tables();
            void handle_add_contact();
            void handle_add_phone();
            void handle_update_contact();
            void handle_remove_phone();
            void handle_remove_contact();
            void handle_find_contacts();
            void handle_list_contacts();

            void print_contact(const entities::Contact& contact) const;
            void print_contacts(const std::vector<entities::Contact>& contacts) const;

            std::string get_input(std::string_view prompt) const;
            int get_int_input(std::string_view prompt) const;

            template<typename... Args>
            void print(Args&&... args) const
            {
                (std::cout << ... << args);
            }

            template<typename... Args>
            void println(Args&&... args) const
            {
                print(std::forward<Args>(args)...);
                std::cout << '\n';
            }
    };
}

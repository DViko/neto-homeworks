#pragma once

#include "cli/dispatcher.hpp"

#include "repository/icontact_repository.hpp"
#include "entity/contact_entity.hpp"

#include "utils/console_io.hpp"

namespace cli
{
    class CLI
    {
        public:
            explicit CLI(repository::IContactRepository& repo);
            void run();

        private:
            repository::IContactRepository& repository_;
            cli::CommandDispatcher dispatcher_;
            bool is_running_{ true };
            std::string in_context_{};

            std::string build_prompt_() const;

            void update_field_(std::string& field, std::string_view label);
            void output_(const std::vector<entity::Contact>& contacts);

            void register_commands_();
            void show_menu_() const;

            void create_tables_();

            void insert_contact_();
            void update_contact_();
            void remove_contact_();

            void insert_phone_();
            void update_phone_();
            void remove_phone_();

            void find_contact_();
            void list_contacts_();    
    };
}

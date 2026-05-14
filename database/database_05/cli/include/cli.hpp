#pragma once

#include "user_repository.hpp"

#include <iostream>
#include <string>
#include <limits>

namespace cli
{
    class UserCLI
    {
        private:
            repositories::UserRepository& m_repo;

            void show_menu();
            void handle_create_table();
            void handle_add_user();
            void handle_update_user();
            void handle_remove_user();
            void handle_list_users();
            void handle_get_user_by_id();

            std::string get_input(const std::string& prompt);
            int get_int_input(const std::string& prompt);

        public:
            explicit UserCLI(repositories::UserRepository& repo);

            void run();
    };
}
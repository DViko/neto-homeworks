#pragma once

#include "client.hpp"
#include "client_repository.hpp"

#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace cli
{
    class ClientCLI
    {
        public:
            explicit ClientCLI(repositories::ClientRepository& repo);
            void run();

        private:
            bool m_running { true };
            repositories::ClientRepository& m_repo;
            using CommandHandler = std::function<void()>;
            std::unordered_map<std::string, CommandHandler > m_commands;

            void register_commands();
            void show_menu();

            void handle_create_tables();
            void handle_add_client();
            void handle_add_phone();

            void handle_update_client();

            void handle_remove_phone();
            void handle_remove_client();

            void handle_find_clients();
            void handle_list_clients();

            void print_client(const entities::Client& client);
            void print_clients(const std::vector<entities::Client>& clients);

            std::string get_input(const std::string& prompt);

            int get_int_input(const std::string& prompt);

            std::vector<std::string>get_phones_input();

            template<typename T>
            void println(const T& value)
            {
                std::cout << value;
            }

            template<typename... Args>
            void println(Args&&... args)
            {
                (std::cout << ... << args) << '\n';
            }
    };
}
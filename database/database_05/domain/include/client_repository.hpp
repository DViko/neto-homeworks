#pragma once

#include "client.hpp"
#include "dbase/connection.hpp"

#include <vector>
#include <string>

namespace repositories
{
    struct Phone
    {
        int id;
        int client_id;
        std::string phone_number;
    };

    class ClientRepository
    {
        private:
            dbase::Connection& m_db;

        public:
            explicit ClientRepository(dbase::Connection& db);

            void create_tables();

            void add_client(const entities::Client& client);
            void add_phone(int client_id, const std::string& phone);

            void update_client(const entities::Client& client);

            void remove_phone(int phone_id);
            void remove_client(int client_id);

            std::vector<entities::Client> find_clients(const std::string& search_term);
            std::vector<entities::Client> get_all_clients();
    };
}
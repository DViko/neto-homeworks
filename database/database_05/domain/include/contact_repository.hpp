#pragma once

#include "contact.hpp"
#include "dbase/connection.hpp"

#include <vector>
#include <string>
#include <optional>

namespace repositories
{
    class ContactRepository
    {
        private:
            dbase::Connection& m_db;

            template<typename Func>
            void execute_transaction(Func&& func, const std::string& error_msg);
            std::vector<entities::Contact> execute_contact_query(
                const std::string& sql,
                const pqxx::params& params = {}
            );

        public:
            explicit ContactRepository(dbase::Connection& db);

            void create_tables();

            void add_contact(const entities::Contact& contact);
            void add_phone(int contact_id, const std::string& phone);

            void update_contact(const entities::Contact& contact);

            void remove_phone(int phone_id);
            void remove_contact(int contact_id);
            std::optional<entities::Contact> get_contact_by_id(int contact_id);

            std::vector<entities::Contact> find_contacts(const std::string& search_term);
            std::vector<entities::Contact> get_all_contacts();
    };
}
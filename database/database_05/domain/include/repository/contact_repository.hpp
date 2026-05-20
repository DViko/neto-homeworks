#pragma once

#include "postgre/connection.hpp"

#include "repository/icontact_repository.hpp"
#include "repository/contact_queries.hpp"

#include <stdexcept>

namespace repository
{
    class ContactRepository : public IContactRepository
    {
        private:

            postgre::Connection& db_;

            template<typename Func>
            void execute_transaction(Func&& action, const std::string& ex_msg)
            {
                try
                {
                    pqxx::work tx(db_.connection());
                    std::forward<Func>(action)(tx);
                    tx.commit();
                }
                catch (const std::exception& e)
                {
                    throw std::runtime_error(ex_msg + ": " + e.what());
                }
            };

        public:
        
            explicit ContactRepository(postgre::Connection& db);

            void create_tables();

            void insert_contact(const entity::Contact& contact);
            void update_contact(const entity::Contact& contact);
            void remove_contact(int contact_id);

            void insert_phone(int contact_id, const std::string_view phone);        
            void update_phone(int phone_id, const std::string_view new_phone);
            void remove_phone(int phone_id);
            
            std::vector<entity::Contact> find_contact(const std::string_view search_term);

            std::vector<entity::Contact> select_contact_list();
            std::optional<entity::Contact> select_contact_by_id(int contact_id);
            std::optional<entity::Contact> select_phone_by_id(int phone_id);
    };
}
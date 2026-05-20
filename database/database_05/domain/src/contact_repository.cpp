#include "repository/contact_repository.hpp"

#include <pqxx/pqxx>
#include <string>

namespace repository
{
    namespace
    {
        entity::Contact map_contact_base(const pqxx::row& row)
        {
            return
            {
                row["id"].as<int>(),
                row["first_name"].as<std::string>(),
                row["last_name"].as<std::string>(),
                row["email"].as<std::string>(),
            };

        }

        std::vector<entity::Contact> build_contacts_from_rows(const pqxx::result& result)
        {
            std::vector<entity::Contact> contacts;
            contacts.reserve(result.size());

            std::optional<int> last_id;

            for (const auto& row : result)
            {
                int id = row["id"].as<int>();
                
                if (!last_id || id != *last_id)
                {
                    contacts.push_back(map_contact_base(row));
                    last_id = id;
                }
                
                if (!row["phone_number"].is_null())
                {
                    contacts.back().phones.emplace_back(
                        row["phone_id"].as<int>(),
                        row["phone_number"].as<std::string>()
                    );
                }
            }

            return contacts;
        }
    }

    ContactRepository::ContactRepository(postgre::Connection& db) : db_(db)
    {
    }

    void ContactRepository::create_tables()
    {
        execute_transaction([](pqxx::work& tx)
        {
            tx.exec(queries::create_contacts_table);
            tx.exec(queries::create_phones_table);
        },
        "Failed to create tables");
    }

    void ContactRepository::insert_contact(const entity::Contact& contact)
    {
        execute_transaction([&contact](pqxx::work& tx)
        {
            auto result = tx.exec(
                queries::insert_contact,
                pqxx::params{contact.first_name, contact.last_name, contact.email}
            );

            int contact_id = result[0][0].as<int>();

            for (const auto& phone : contact.phones)
            {
                tx.exec(
                    queries::insert_phone,
                    pqxx::params{contact_id, phone.number}
                );
            }
        }, "Failed to add contact");
    }

     void ContactRepository::update_contact(const entity::Contact& contact)
    {
        execute_transaction([contact](pqxx::work& tx) {
            tx.exec(
                queries::update_contact,
                pqxx::params{contact.first_name, contact.last_name, contact.email, contact.id}
            );

            if (!contact.phones.empty())
            {
                tx.exec(
                    queries::delete_phones_by_contact_id,
                    pqxx::params{contact.id}
                );

                for (const auto& phone : contact.phones)
                {
                    tx.exec(
                        queries::insert_phone,
                        pqxx::params{contact.id, phone.number}
                    );
                }
            }
        }, "Failed to update contact");
    }

    void ContactRepository::remove_contact(int contact_id)
    {
        execute_transaction([contact_id](pqxx::work& tx) {
            tx.exec(
                queries::delete_contact,
                pqxx::params{contact_id}
            );
        }, "Failed to remove contact");
    }

    void ContactRepository::insert_phone(int contact_id, const std::string_view phone)
    {
        execute_transaction([contact_id, phone](pqxx::work& tx) {
                tx.exec(
                    queries::insert_phone,
                    pqxx::params{contact_id, phone}
                );
        }, "Failed to add phone");
    }

    void ContactRepository::update_phone(int phone_id, const std::string_view new_number)
    {
        execute_transaction([phone_id, new_number](pqxx::work& tx) {
            tx.exec(
                queries::update_phone,
                pqxx::params{new_number, phone_id}
            );
        }, "Failed to update phone");
    }

    void ContactRepository::remove_phone(int phone_id)
    {
        execute_transaction([phone_id](pqxx::work& tx) {
            tx.exec(
                queries::delete_phone,
                pqxx::params{phone_id}
            );
        }, "Failed to remove phone");
    }

    std::vector<entity::Contact> ContactRepository::find_contact(const std::string_view term)
    {
        pqxx::read_transaction tx(db_.connection());

        return build_contacts_from_rows(
            tx.exec(
                queries::find_contact,
                pqxx::params{"%" + std::string(term) + "%"}
            )
        );
    }

    std::vector<entity::Contact> ContactRepository::select_contact_list()
    {
        pqxx::read_transaction tx(db_.connection());

        return build_contacts_from_rows(
            tx.exec(
                queries::select_contact_list
            )
        );
    }

    std::optional<entity::Contact> ContactRepository::select_contact_by_id(int contact_id)
    {
        pqxx::read_transaction tx(db_.connection());

        const auto contacts = build_contacts_from_rows(
            tx.exec(
                queries::select_contact_by_id,
                pqxx::params{contact_id}
            )
        );

        return contacts.empty() ? std::nullopt : std::optional<entity::Contact>{std::move(contacts[0])};
    }

    std::optional<entity::Contact> ContactRepository::select_phone_by_id(int phone_id)
    {
        pqxx::read_transaction tx(db_.connection());

        const auto contacts = build_contacts_from_rows(
            tx.exec(
                queries::select_phone_by_id,
                pqxx::params{phone_id}
            )
        );

        return contacts.empty() ? std::nullopt : std::optional<entity::Contact>{std::move(contacts[0])};
    }
}
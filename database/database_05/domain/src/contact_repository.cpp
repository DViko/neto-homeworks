#include "contact_repository.hpp"

#include <pqxx/pqxx>
#include <map>

namespace repositories
{
    namespace
    {
        entities::Contact map_contact_base(const pqxx::row& row)
        {
            entities::Contact contact;

            contact.id         = row["id"].as<int>();
            contact.first_name = row["first_name"].as<std::string>();
            contact.last_name  = row["last_name"].as<std::string>();
            contact.email      = row["email"].as<std::string>();

            return contact;
        }

        void insert_phone(pqxx::work& tx, int contact_id, const std::string& phone)
        {
            tx.exec(
                "INSERT INTO phones (contact_id, phone_number) VALUES ($1, $2)",
                pqxx::params{contact_id, phone}
            );
        }

        std::vector<entities::Contact> build_contacts_from_rows(const pqxx::result& result)
        {
            std::map<int, entities::Contact> contacts_map;

            for (const auto& row : result)
            {
                const int id = row["id"].as<int>();

                auto& contact = contacts_map.try_emplace(id, map_contact_base(row)).first->second;

                if (!row["phone_number"].is_null())
                {
                    contact.phones.push_back({ row["phone_id"].as<int>(), row["phone_number"].as<std::string>() });
                }
            }

            std::vector<entities::Contact> contacts;
            contacts.reserve(contacts_map.size());

            for (auto& [_, contact] : contacts_map)
            {
                contacts.emplace_back(std::move(contact));
            }

            return contacts;
        }
    }

    ContactRepository::ContactRepository(dbase::Connection& db) : m_db(db)
    {
    }

    std::vector<entities::Contact> ContactRepository::execute_contact_query(
        const std::string& sql,
        const pqxx::params& params
    )
    {
        pqxx::work tx(m_db.connection());
        auto result = tx.exec(sql, params);
        return build_contacts_from_rows(result);
    }

    template<typename Func>
    void ContactRepository::execute_transaction(Func&& func, const std::string& error_msg)
    {
        try
        {
            pqxx::work tx(m_db.connection());
            std::forward<Func>(func)(tx);
            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error(error_msg + ": " + e.what());
        }
    }

    void ContactRepository::create_tables()
    {
        execute_transaction([](pqxx::work& tx) {
            tx.exec(
                R"(
                    CREATE TABLE IF NOT EXISTS contacts
                    (
                        id SERIAL PRIMARY KEY,
                        first_name TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT UNIQUE NOT NULL
                    )
                )"
            );

            tx.exec(
                R"(
                    CREATE TABLE IF NOT EXISTS phones
                    (
                        id SERIAL PRIMARY KEY,
                        contact_id INTEGER REFERENCES contacts(id) ON DELETE CASCADE,
                        phone_number TEXT NOT NULL
                    )
                )"
            );
        }, "Failed to create tables");
    }

    void ContactRepository::add_contact(const entities::Contact& contact)
    {
        execute_transaction([&contact](pqxx::work& tx) {
            auto result = tx.exec(
                "INSERT INTO contacts (first_name, last_name, email) VALUES ($1, $2, $3) RETURNING id",
                pqxx::params{contact.first_name, contact.last_name, contact.email}
            );

            int contact_id = result[0][0].as<int>();

            for (const auto& phone : contact.phones)
            {
                insert_phone(tx, contact_id, phone.number);
            }
        }, "Failed to add contact");
    }

    void ContactRepository::add_phone(int contact_id, const std::string& phone)
    {
        execute_transaction([contact_id, &phone](pqxx::work& tx) {
            insert_phone(tx, contact_id, phone);
        }, "Failed to add phone");
    }

    void ContactRepository::update_contact(const entities::Contact& contact)
    {
        execute_transaction([&contact](pqxx::work& tx) {
            tx.exec(
                "UPDATE contacts SET first_name = $1, last_name = $2, email = $3 WHERE id = $4",
                pqxx::params{contact.first_name, contact.last_name, contact.email, contact.id}
            );

            if (!contact.phones.empty())
            {
                tx.exec(
                    "DELETE FROM phones WHERE contact_id = $1",
                    pqxx::params{contact.id}
                );

                for (const auto& phone : contact.phones)
                {
                    insert_phone(tx, contact.id, phone.number);
                }
            }
        }, "Failed to update contact");
    }

    void ContactRepository::remove_phone(int phone_id)
    {
        execute_transaction([phone_id](pqxx::work& tx) {
            tx.exec(
                "DELETE FROM phones WHERE id = $1",
                pqxx::params{phone_id}
            );
        }, "Failed to remove phone");
    }

    void ContactRepository::remove_contact(int contact_id)
    {
        execute_transaction([contact_id](pqxx::work& tx) {
            tx.exec(
                "DELETE FROM contacts WHERE id = $1",
                pqxx::params{contact_id}
            );
        }, "Failed to remove contact");
    }

    std::vector<entities::Contact> ContactRepository::get_all_contacts()
    {
        return execute_contact_query(
            R"(
                SELECT c.id, c.first_name, c.last_name, c.email, p.id AS phone_id, p.phone_number
                FROM contacts c
                LEFT JOIN phones p ON c.id = p.contact_id
                ORDER BY c.id
            )"
        );
    }

    std::optional<entities::Contact> ContactRepository::get_contact_by_id(int contact_id)
    {
        const auto contacts = execute_contact_query(
            R"(
                SELECT c.id, c.first_name, c.last_name, c.email, p.id AS phone_id, p.phone_number
                FROM contacts c
                LEFT JOIN phones p ON c.id = p.contact_id
                WHERE c.id = $1
                ORDER BY p.id
            )",
            pqxx::params{contact_id}
        );

        return contacts.empty() ? std::nullopt : std::optional<entities::Contact>{contacts[0]};
    }

    std::vector<entities::Contact> ContactRepository::find_contacts(const std::string& term)
    {
        return execute_contact_query(
            R"(
                SELECT c.id, c.first_name, c.last_name, c.email, p.id AS phone_id, p.phone_number
                FROM contacts c
                LEFT JOIN phones p ON c.id = p.contact_id
                WHERE c.first_name ILIKE $1
                OR c.last_name  ILIKE $1
                OR c.email      ILIKE $1
                OR p.phone_number ILIKE $1
                ORDER BY c.id
            )",
            pqxx::params{"%" + term + "%"}
        );
    }
}
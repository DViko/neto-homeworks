#include "client_repository.hpp"

#include <pqxx/pqxx>

namespace repositories
{
    namespace
    {
        entities::Client map_client_base(const pqxx::row& row)
        {
            entities::Client client;

            client.id         = row["id"].as<int>();
            client.first_name = row["first_name"].as<std::string>();
            client.last_name  = row["last_name"].as<std::string>();
            client.email      = row["email"].as<std::string>();

            return client;
        }

        std::vector<entities::Client> build_clients_from_rows(const pqxx::result& result)
        {
            std::unordered_map<int, entities::Client> clients_map;

            for (const auto& row : result)
            {
                const int id = row["id"].as<int>();

                auto& client = clients_map.try_emplace(id, map_client_base(row)).first->second;

                if (!row["phone_number"].is_null())
                {
                    client.phones.push_back(row["phone_number"].as<std::string>());
                }
            }

            std::vector<entities::Client> clients;
            clients.reserve(clients_map.size());

            for (auto& [_, client] : clients_map)
            {
                clients.emplace_back(std::move(client));
            }

            return clients;
        }
    }

    ClientRepository::ClientRepository(dbase::Connection& db) : m_db(db)
    {
    }

    template<typename Func>
    void ClientRepository::execute_transaction(Func&& func, const std::string& error_msg)
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

    void ClientRepository::create_tables()
    {
        execute_transaction([](pqxx::work& tx) {
            tx.exec(
                R"(
                    CREATE TABLE IF NOT EXISTS clients
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
                        client_id INTEGER REFERENCES clients(id) ON DELETE CASCADE,
                        phone_number TEXT NOT NULL
                    )
                )"
            );
        }, "Failed to create tables");
    }

    void ClientRepository::add_client(const entities::Client& client)
    {
        execute_transaction([&client](pqxx::work& tx) {
            auto result = tx.exec(
                "INSERT INTO clients (first_name, last_name, email) VALUES ($1, $2, $3) RETURNING id",
                pqxx::params{client.first_name, client.last_name, client.email}
            );

            int client_id = result[0][0].as<int>();

            for (const auto& phone : client.phones)
            {
                tx.exec(
                    "INSERT INTO phones (client_id, phone_number) VALUES ($1, $2)",
                    pqxx::params{client_id, phone}
                );
            }
        }, "Failed to add client");
    }

    void ClientRepository::add_phone(int client_id, const std::string& phone)
    {
        execute_transaction([client_id, &phone](pqxx::work& tx) {
            tx.exec(
                "INSERT INTO phones (client_id, phone_number) VALUES ($1, $2)",
                pqxx::params{client_id, phone}
            );
        }, "Failed to add phone");
    }

    void ClientRepository::update_client(const entities::Client& client)
    {
        execute_transaction([&client](pqxx::work& tx) {
            tx.exec(
                "UPDATE clients SET first_name = $1, last_name = $2, email = $3 WHERE id = $4",
                pqxx::params{client.first_name, client.last_name, client.email, client.id}
            );

            tx.exec(
                "DELETE FROM phones WHERE client_id = $1",
                pqxx::params{client.id}
            );

            for (const auto& phone : client.phones)
            {
                tx.exec(
                    "INSERT INTO phones (client_id, phone_number) VALUES ($1, $2)",
                    pqxx::params{client.id, phone}
                );
            }
        }, "Failed to update client");
    }

    void ClientRepository::remove_phone(int phone_id)
    {
        execute_transaction([phone_id](pqxx::work& tx) {
            tx.exec(
                "DELETE FROM phones WHERE id = $1",
                pqxx::params{phone_id}
            );
        }, "Failed to remove phone");
    }

    void ClientRepository::remove_client(int client_id)
    {
        execute_transaction([client_id](pqxx::work& tx) {
            tx.exec(
                "DELETE FROM clients WHERE id = $1",
                pqxx::params{client_id}
            );
        }, "Failed to remove client");
    }

    std::vector<entities::Client> ClientRepository::get_all_clients()
    {
        pqxx::work tx(m_db.connection());

        auto result = tx.exec(
            R"(
                SELECT c.id, c.first_name, c.last_name, c.email, p.phone_number
                FROM clients c
                LEFT JOIN phones p ON c.id = p.client_id
                ORDER BY c.id
            )"
        );

        return build_clients_from_rows(result);
    }

    std::vector<entities::Client> ClientRepository::find_clients(const std::string& term)
    {
        pqxx::work tx(m_db.connection());

        auto result = tx.exec(
            R"(
                SELECT c.id, c.first_name, c.last_name, c.email, p.phone_number
                FROM clients c
                LEFT JOIN phones p ON c.id = p.client_id
                WHERE c.first_name ILIKE $1
                OR c.last_name  ILIKE $1
                OR c.email      ILIKE $1
                OR p.phone_number ILIKE $1
                ORDER BY c.id
            )",
            pqxx::params{"%" + term + "%"}
        );

        return build_clients_from_rows(result);
    }
}
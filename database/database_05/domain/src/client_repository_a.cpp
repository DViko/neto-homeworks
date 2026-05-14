#include "client_repository.hpp"

#include <pqxx/pqxx>

namespace repositories
{
    ClientRepository::ClientRepository(dbase::Connection& db) : m_db(db)
    {
    }

    void ClientRepository::create_tables()
    {
        try
        {
            pqxx::work tx(m_db.connection());

            tx.exec(R"(
                CREATE TABLE IF NOT EXISTS clients
                (
                    id SERIAL PRIMARY KEY,
                    first_name TEXT NOT NULL,
                    last_name TEXT NOT NULL,
                    email TEXT UNIQUE NOT NULL
                )
            )");

            tx.exec(R"(
                CREATE TABLE IF NOT EXISTS phones
                (
                    id SERIAL PRIMARY KEY,
                    client_id INTEGER REFERENCES clients(id) ON DELETE CASCADE,
                    phone_number TEXT NOT NULL
                )
            )");

            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to create tables: " + std::string(e.what()));
        }
    }

    void ClientRepository::add_client(const entities::Client& client)
    {
        try
        {
            pqxx::work tx(m_db.connection());

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

            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to add client: " + std::string(e.what()));
        }
    }

    void ClientRepository::add_phone(int client_id, const std::string& phone)
    {
        try
        {
            pqxx::work tx(m_db.connection());

            tx.exec(
                "INSERT INTO phones (client_id, phone_number) VALUES ($1, $2)",
                pqxx::params{client_id, phone}
            );

            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to add phone: " + std::string(e.what()));
        }
    }

    void ClientRepository::update_client(const entities::Client& client)
    {
        try
        {
            pqxx::work tx(m_db.connection());

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

            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to update client: " + std::string(e.what()));
        }
    }

    void ClientRepository::remove_phone(int phone_id)
    {
        try
        {
            pqxx::work tx(m_db.connection());

            tx.exec(
                "DELETE FROM phones WHERE id = $1",
                pqxx::params{phone_id}
            );

            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to remove phone: " + std::string(e.what()));
        }
    }

    void ClientRepository::remove_client(int client_id)
    {
        try
        {
            pqxx::work tx(m_db.connection());

            tx.exec(
                "DELETE FROM clients WHERE id = $1",
                pqxx::params{client_id}
            );

            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to remove client: " + std::string(e.what()));
        }
    }

    std::vector<entities::Client> ClientRepository::find_clients(const std::string& search_term)
    {
        try
        {
            pqxx::work tx(m_db.connection());

            auto result = tx.exec
            (
                R"(
                SELECT DISTINCT c.id, c.first_name, c.last_name, c.email
                FROM clients c
                LEFT JOIN phones p ON c.id = p.client_id
                WHERE c.first_name ILIKE $1
                   OR c.last_name ILIKE $1
                   OR c.email ILIKE $1
                   OR p.phone_number ILIKE $1
            )", pqxx::params{"%" + search_term + "%"});

            std::vector<entities::Client> clients;

            for (const auto& row : result)
            {
                entities::Client client;
                client.id = row[0].as<int>();
                client.first_name = row[1].as<std::string>();
                client.last_name = row[2].as<std::string>();
                client.email = row[3].as<std::string>();

                auto phone_result = tx.exec(
                    "SELECT phone_number FROM phones WHERE client_id = $1",
                    pqxx::params{client.id}
                );
                for (const auto& phone_row : phone_result)
                {
                    client.phones.push_back(phone_row[0].as<std::string>());
                }

                clients.push_back(client);
            }

            return clients;
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to find clients: " + std::string(e.what()));
        }
    }

    std::vector<entities::Client> ClientRepository::get_all_clients()
    {
        try
        {
            pqxx::work tx(m_db.connection());

            auto result = tx.exec("SELECT id, first_name, last_name, email FROM clients");

            std::vector<entities::Client> clients;
            for (const auto& row : result)
            {
                entities::Client client;
                client.id = row[0].as<int>();
                client.first_name = row[1].as<std::string>();
                client.last_name = row[2].as<std::string>();
                client.email = row[3].as<std::string>();

                auto phone_result = tx.exec(
                    "SELECT phone_number FROM phones WHERE client_id = $1",
                    pqxx::params{client.id}
                );
                for (const auto& phone_row : phone_result)
                {
                    client.phones.push_back(phone_row[0].as<std::string>());
                }

                clients.push_back(client);
            }

            return clients;
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to get all clients: " + std::string(e.what()));
        }
    }
}
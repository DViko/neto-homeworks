#include "user_repository.hpp"

#include <pqxx/pqxx>

namespace repositories
{
    UserRepository::UserRepository(dbase::Connection& db) : m_db(db)
    {
    }

    void UserRepository::create_table()
    {
        try
        {
            pqxx::work tx(m_db.connection());

            tx.exec(R"(
                CREATE TABLE IF NOT EXISTS users
                (
                    id SERIAL PRIMARY KEY,
                    name TEXT NOT NULL
                )
            )");

            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to create table: " + std::string(e.what()));
        }
    }

    void UserRepository::add(const entities::User& user)
    {
        try
        {
            pqxx::work tx(m_db.connection());

            tx.exec(
                "INSERT INTO users (name) VALUES ($1)",
                pqxx::params{user.name}
            );

            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to add user: " + std::string(e.what()));
        }
    }

    std::vector<entities::User> UserRepository::get_all()
    {
        try
        {
            pqxx::work tx(m_db.connection());

            auto result = tx.exec("SELECT id, name FROM users");

            std::vector<entities::User> users;
            users.reserve(result.size());

            for (const auto& row : result)
            {
                entities::User user;
                user.id = row[0].as<int>();
                user.name = row[1].as<std::string>();

                users.push_back(user);
            }

            return users;
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to get users: " + std::string(e.what()));
        }
    }

    void UserRepository::update(const entities::User& user)
    {
        try
        {
            pqxx::work tx(m_db.connection());

            tx.exec(
                "UPDATE users SET name = $1 WHERE id = $2",
                pqxx::params{user.name, user.id}
            );

            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to update user: " + std::string(e.what()));
        }
    }

    void UserRepository::remove(int id)
    {
        try
        {
            pqxx::work tx(m_db.connection());

            tx.exec(
                "DELETE FROM users WHERE id = $1",
                pqxx::params{id}
            );

            tx.commit();
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to remove user: " + std::string(e.what()));
        }
    }

    std::optional<entities::User> UserRepository::get_by_id(int id)
    {
        try
        {
            pqxx::work tx(m_db.connection());

            auto result = tx.exec(
                "SELECT id, name FROM users WHERE id = $1",
                pqxx::params{id}
            );

            if (result.empty())
            {
                return std::nullopt;
            }

            entities::User user;
            user.id = result[0][0].as<int>();
            user.name = result[0][1].as<std::string>();

            return user;
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to get user by id: " + std::string(e.what()));
        }
    }
}
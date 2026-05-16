#include "dbase/connection.hpp"

#include <stdexcept>

namespace dbase
{
    Connection::Connection(const std::string& connection_string) : m_connection_string(connection_string)
    {
        m_connection = std::make_unique<pqxx::connection>(m_connection_string);

        if (!m_connection->is_open())
        {
            throw std::runtime_error("Failed to open DB connection");
        }
    }

    bool Connection::is_connected() const
    {
        return m_connection && m_connection->is_open();
    }

    pqxx::connection& Connection::connection()
    {
        if (!m_connection)
        {
            throw std::runtime_error("DB not connected");
        }

        return *m_connection;
    }

    std::string Connection::get_server_version()
    {
        auto& conn = connection();

        pqxx::work tx(conn);

        auto result{ tx.exec("SELECT version();") };

        if (result.empty())
        {
            throw std::runtime_error("Failed to get server version");
        }

        return result[0][0].as<std::string>();
    }
}
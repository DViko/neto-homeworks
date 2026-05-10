#include "dbase/connection.hpp"
#include "dbase/connection_string_builder.hpp"

#include <stdexcept>
#include <iostream>

namespace dbase
{
    Connection::Connection(const config::DatabaseConfig& config) : m_connection(build_connection_string(config))
    {
        if (!m_connection.is_open())
        {
            throw std::runtime_error("Failed to open DB connection");
        }
    }

    void Connection::test_connection()
    {
        pqxx::work tx(m_connection);

        auto result = tx.exec("SELECT version();");

        std::cout << result[0][0].c_str() << std::endl;
    }
}
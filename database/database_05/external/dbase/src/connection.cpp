#include "postgre/connection.hpp"

#include <stdexcept>

namespace postgre
{
    Connection::Connection(const std::string& connection_string) : connection_string_(connection_string)
    {
        connection_ = std::make_unique<pqxx::connection>(connection_string_);

        if (!connection_->is_open())
        {
            throw std::runtime_error("Failed to open DB connection");
        }
    }

    pqxx::connection& Connection::connection()
    {
        if (!connection_)
        {
            throw std::runtime_error("DB not connected");
        }

        return *connection_;
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
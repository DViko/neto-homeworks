#pragma once

#include <pqxx/pqxx>
#include <string>

namespace dbase
{
    class Connection
    {
        private:
            std::string m_connection_string;
            std::unique_ptr<pqxx::connection> m_connection;

        public:
            explicit Connection(const std::string& connection_string);
            bool is_connected() const;

            pqxx::connection& connection();
            std::string get_server_version();
    };
}
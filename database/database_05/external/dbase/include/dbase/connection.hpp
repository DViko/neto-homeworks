#pragma once

#include "config/db_config.hpp"
#include <pqxx/pqxx>
#include <string>

namespace dbase
{
    class Connection
    {
        private:
            pqxx::connection m_connection;

        public:
            explicit Connection(const config::DatabaseConfig& config);

            void test_connection();

    };
}
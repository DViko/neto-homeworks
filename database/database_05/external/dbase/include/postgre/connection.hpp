#pragma once

#include "postgre/config.hpp"
#include <pqxx/pqxx>
#include <string>

namespace postgre
{
    class Connection
    {
        private:
            std::string connection_string_;
            std::unique_ptr<pqxx::connection> connection_;

        public:
            explicit Connection(const std::string& connection_string);
            
            pqxx::connection& connection();
            std::string get_server_version();
    };
}
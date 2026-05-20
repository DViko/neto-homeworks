#pragma once

#include <string>

namespace postgre
{
    struct Config
    {
        std::string host{ "127.0.0.1" };
        int port{ 5432 };
        std::string dbname{ "ContactsDB" };
        std::string user{ "postgres" };
        std::string password{ "root" };

        std::string to_string() const
        {
            return "host=" + host + " port=" + std::to_string(port) + " dbname=" + dbname +
                   " user=" + user + " password=" + password;
        }
    };
}
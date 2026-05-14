#pragma once

#include <string>

namespace dbase
{
    struct DbConfig
    {
        std::string host{ "127.0.0.1" };
        int port{ 5432 };
        std::string dbname{ "UserDatabase" };
        std::string user{ "postgres" };
        std::string password{ "root" };
    };
}
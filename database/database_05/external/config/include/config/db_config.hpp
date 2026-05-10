#pragma once

#include <string>

namespace config
{
    struct DatabaseConfig
    {
        std::string host;
        int port;
        std::string dbname;
        std::string user;
        std::string password;
    };
}
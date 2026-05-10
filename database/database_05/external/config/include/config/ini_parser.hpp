#pragma once

#include "config/db_config.hpp"

#include <string>

namespace config
{
    class IniParser
    {
        public:
            static DatabaseConfig load_db_config(const std::string& filepath);
    };
}
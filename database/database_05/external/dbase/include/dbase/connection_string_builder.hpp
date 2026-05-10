#pragma once

#include "config/db_config.hpp"
#include <string>

namespace dbase
{
    std::string build_connection_string(const config::DatabaseConfig& cconfig);
}
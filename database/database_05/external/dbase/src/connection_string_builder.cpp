#include "dbase/connection_string_builder.hpp"

#include <string>

namespace dbase
{
    std::string build_connection_string(const config::DatabaseConfig& config)
    {
        return  "host=" + config.host + " port=" + std::to_string(config.port) + " dbname=" + config.dbname +
                " user=" + config.user + " password=" + config.password;
    }
}
#include "config/ini_parser.hpp"
#include "dbase/connection.hpp"
#include <iostream>

int main()
{
    try
    {
        dbase::Connection db(config::IniParser::load_db_config("external/dbase/db_config.ini"));

        db.test_connection();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Fatal error: " << exception.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
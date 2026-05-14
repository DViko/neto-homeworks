#include "dbase/config.hpp"
#include "dbase/connection.hpp"

#include "user_repository.hpp"
#include "cli.hpp"

#include <iostream>

std::string build_connection_string(const dbase::DbConfig& config);

int main()
{
    dbase::DbConfig config;
    config.dbname = "UserDatabase";

    try
    {
        dbase::Connection db(build_connection_string(config));

        db.connect();

        std::cout << "Connected to database. Server version: " << db.get_server_version() << '\n';

        repositories::UserRepository repo(db);
        cli::UserCLI user_cli(repo);

        user_cli.run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

std::string build_connection_string(const dbase::DbConfig& config)
{
    return  "host=" + config.host + " port=" + std::to_string(config.port) + " dbname=" + config.dbname +
            " user=" + config.user + " password=" + config.password;
}
#include "dbase/config.hpp"
#include "dbase/connection.hpp"

#include "client_repository.hpp"
#include "client_cli.hpp"

#include <iostream>

int main()
{
    dbase::DbConfig config;

    try
    {
        dbase::Connection db(config.to_string());

        std::cout << "Server version: " << db.get_server_version() << '\n';

        repositories::ClientRepository repo(db);
        cli::ClientCLI client_cli(repo);

        client_cli.run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
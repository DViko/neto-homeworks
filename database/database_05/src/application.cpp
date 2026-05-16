#include "application.hpp"

#include <iostream>

namespace app
{
    Application::Application()
        : m_connection(m_config.to_string())
        , m_repository(m_connection)
        , m_cli(m_repository)
    {
    }

    int Application::run()
    {
        std::cout << "Server version: " << m_connection.get_server_version() << '\n';
        m_cli.run();
        return EXIT_SUCCESS;
    }
}

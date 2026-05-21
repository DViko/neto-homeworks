#include "application.hpp"

#include <iostream>

namespace app
{
    Application::Application() : connection_(config_.to_string()), repository_(connection_), cli_(repository_)
    {
    }

    int Application::run()
    {
        std::cout << "Server version: " << connection_.get_server_version() << '\n';
        
        cli_.run();
        return EXIT_SUCCESS;
    }
}

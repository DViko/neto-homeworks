#pragma once

#include "postgre/config.hpp"
#include "postgre/connection.hpp"

#include "repository/contact_repository.hpp"
#include "cli/contact_cli.hpp"


namespace app
{
    class Application
    {
        public:
            Application();
            int run();

        private:
            postgre::Config config_;
            postgre::Connection connection_;
            repository::ContactRepository repository_;
            cli::CLI cli_;
    };
}

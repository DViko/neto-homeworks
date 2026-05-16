#pragma once

#include "dbase/config.hpp"
#include "dbase/connection.hpp"
#include "contact_repository.hpp"
#include "contact_cli.hpp"

namespace app
{
    class Application
    {
        public:
            Application();
            int run();

        private:
            dbase::DbConfig m_config;
            dbase::Connection m_connection;
            repositories::ContactRepository m_repository;
            cli::ContactCLI m_cli;
    };
}

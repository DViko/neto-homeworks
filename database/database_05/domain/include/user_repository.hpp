#pragma once

#include "user.hpp"
#include "dbase/connection.hpp"

#include <vector>
#include <optional>

namespace repositories
{
    class UserRepository
    {
        private:
            dbase::Connection& m_db;

        public:
            explicit UserRepository(dbase::Connection& db);

            void create_table();

            void add(const entities::User& user);
            void update(const entities::User& user);
            void remove(int id);

            std::vector<entities::User> get_all();
            std::optional<entities::User> get_by_id(int id);
    };
}
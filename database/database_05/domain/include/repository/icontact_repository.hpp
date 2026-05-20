#pragma once

#include "entity/contact_entity.hpp"

#include <string_view>
#include <vector>
#include <optional>

namespace repository
{
    class IContactRepository
    {
        public:
            virtual ~IContactRepository() = default;

            virtual void create_tables() = 0;

            virtual void insert_contact(const entity::Contact& contact) = 0;
            virtual void update_contact(const entity::Contact& contact) = 0;
            virtual void remove_contact(int contact_id) = 0;

            virtual void insert_phone(int contact_id, const std::string_view phone) = 0;
            virtual void update_phone(int phone_id, const std::string_view new_phone) = 0;
            virtual void remove_phone(int phone_id) = 0;

            virtual std::vector<entity::Contact> find_contact(const std::string_view search_term) = 0;

            virtual std::vector<entity::Contact> select_contact_list() = 0;
            virtual std::optional<entity::Contact> select_contact_by_id(int contact_id) = 0;
            virtual std::optional<entity::Contact> select_phone_by_id(int phone_id) = 0;
    };
}
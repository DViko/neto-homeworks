#pragma once

#include <string_view>

namespace repository::queries
{
    inline constexpr std::string_view create_contacts_table = R"(
        CREATE TABLE IF NOT EXISTS contacts (
            id SERIAL PRIMARY KEY,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT UNIQUE NOT NULL
        )
    )";

    inline constexpr std::string_view create_phones_table = R"(
        CREATE TABLE IF NOT EXISTS phones (
            id SERIAL PRIMARY KEY,
            contact_id INTEGER REFERENCES contacts(id) ON DELETE CASCADE,
            phone_number TEXT NOT NULL
        )
    )";

    inline constexpr std::string_view insert_contact = R"(
        INSERT INTO contacts (first_name, last_name, email)
        VALUES ($1, $2, $3)
        RETURNING id
    )";

    inline constexpr std::string_view update_contact = R"(
        UPDATE contacts
        SET first_name = $1, last_name = $2, email = $3
        WHERE id = $4
    )";

    inline constexpr std::string_view delete_contact = R"(
        DELETE FROM contacts WHERE id = $1
    )";

    inline constexpr std::string_view insert_phone = R"(
        INSERT INTO phones (contact_id, phone_number)
        VALUES ($1, $2)
    )";

    inline constexpr std::string_view update_phone = R"(
        UPDATE phones
        SET phone_number = $1
        WHERE id = $2
    )";

    inline constexpr std::string_view delete_phone = R"(
        DELETE FROM phones WHERE id = $1
    )";

    inline constexpr std::string_view delete_phones_by_contact_id = R"(
        DELETE FROM phones WHERE contact_id = $1
    )";

    inline constexpr std::string_view find_contact = R"(
        SELECT DISTINCT c.id, c.first_name, c.last_name, c.email, 
               p.id AS phone_id, p.phone_number
        FROM contacts c
        LEFT JOIN phones p ON c.id = p.contact_id
        WHERE c.first_name ILIKE $1
           OR c.last_name ILIKE $1
           OR c.email ILIKE $1
           OR p.phone_number ILIKE $1
        ORDER BY c.id
    )";

    inline constexpr std::string_view select_contact_list = R"(
        SELECT c.id, c.first_name, c.last_name, c.email,
               p.id AS phone_id, p.phone_number
        FROM contacts c
        LEFT JOIN phones p ON c.id = p.contact_id
        ORDER BY c.id, p.id
    )";

    inline constexpr std::string_view select_contact_by_id = R"(
        SELECT c.id, c.first_name, c.last_name, c.email, 
               p.id AS phone_id, p.phone_number
        FROM contacts c
        LEFT JOIN phones p ON c.id = p.contact_id
        WHERE c.id = $1
        ORDER BY p.id
    )";

    inline constexpr std::string_view select_phone_by_id = R"(
        SELECT id, phone_number
        FROM phones
        WHERE id = $1
    )";
}

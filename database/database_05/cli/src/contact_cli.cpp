#include "contact_cli.hpp"

#include <iostream>

namespace cli
{

    ContactCLI::ContactCLI(repositories::ContactRepository& repo) : m_repo(repo)
    {
        register_commands();
    }

    void ContactCLI::run()
    {
        println("\nType 'help' to show command list\n");

        while (m_running)
        {
            const std::string command = get_input("\nEnter command: ");
            
            const auto it = std::find_if
            (
                m_command_definitions.begin(), m_command_definitions.end(),
                [&command](const CommandDefinition& def) {
                    return def.key == command;
                }
            );

            if (it == m_command_definitions.end())
            {
                println("\nUnknown command. Type 'help'\n");
                continue;
            }

            try
            {
                it->action();
            }
            catch (const std::exception& e)
            {
                println("Error: ", e.what());
            }
        }
    }

    void ContactCLI::register_commands()
    {
        m_command_definitions = {
            {"1", "     Create tables", [this](){ handle_create_tables(); }},
            {"2", "     Add contact", [this](){ handle_add_contact(); }},
            {"3", "     Add phone to contact", [this](){ handle_add_phone(); }},
            {"4", "     Update contact", [this](){ handle_update_contact(); }},
            {"5", "     Remove phone", [this](){ handle_remove_phone(); }},
            {"6", "     Remove contact", [this](){ handle_remove_contact(); }},
            {"7", "     Find contacts", [this](){ handle_find_contacts(); }},
            {"8", "     List all contacts", [this](){ handle_list_contacts(); }},
            {"9", "     Exit", [this](){ m_running = false; }},
            {"help", "  Show command list", [this](){ show_menu(); }}
        };
    }

    void ContactCLI::show_menu() const
    {
        println("\nCommands:  Actions:\n");

        for (const auto& command : m_command_definitions)
        {
            println('\n', command.key, " ", command.description);
        }
    }

    void ContactCLI::handle_create_tables()
    {
        m_repo.create_tables();
        println("\nTables created successfully\n");
    }

    void ContactCLI::handle_add_contact()
    {
        entities::Contact contact{};

        contact.first_name = get_input("First name: ");
        contact.last_name = get_input("Last name: ");
        contact.email = get_input("Email: ");

        const std::string phone = get_input("Phone (optional): ");

        if (!phone.empty())
        {
            contact.phones.push_back({0, phone});
        }

        m_repo.add_contact(contact);
        
        println("\nContact added successfully\n");
    }

    void ContactCLI::handle_add_phone()
    {
        const int contact_id = get_int_input("Contact ID: ");
        const std::string phone = get_input("Phone: ");

        m_repo.add_phone(contact_id, phone);
        println("\nPhone added successfully\n");
    }

    void ContactCLI::handle_update_contact()
    {
        const int contact_id = get_int_input("Contact ID: ");
        const auto existing_contact = m_repo.get_contact_by_id(contact_id);

        if (!existing_contact)
        {
            println("\nContact not found\n");
            return;
        }

        entities::Contact contact = *existing_contact;
        println("Leave fields empty to preserve current values.");

        const auto first_name = get_input("First name [" + contact.first_name + "]: ");
        if (!first_name.empty())
        {
            contact.first_name = first_name;
        }

        const auto last_name = get_input("Last name [" + contact.last_name + "]: ");
        if (!last_name.empty())
        {
            contact.last_name = last_name;
        }

        const auto email = get_input("Email [" + contact.email + "]: ");
        if (!email.empty())
        {
            contact.email = email;
        }

        println("Current phones:");
        if (contact.phones.empty())
        {
            println("  No phones");
        }
        else
        {
            for (const auto& phone : contact.phones)
            {
                println("  [", phone.id, "] ", phone.number);
            }
        }

        m_repo.update_contact(contact);
        println("\nContact updated successfully\n");
    }

    void ContactCLI::handle_remove_phone()
    {
        const int phone_id = get_int_input("Phone ID: ");
        m_repo.remove_phone(phone_id);
        println("\nPhone removed successfully\n");
    }

    void ContactCLI::handle_remove_contact()
    {
        const int contact_id = get_int_input("Contact ID: ");
        m_repo.remove_contact(contact_id);
        println("\nContact removed successfully\n");
    }

    void ContactCLI::handle_find_contacts()
    {
        const std::string term = get_input("Search: ");
        const auto contacts = m_repo.find_contacts(term);
        print_contacts(contacts);
    }

    void ContactCLI::handle_list_contacts()
    {
        const auto contacts = m_repo.get_all_contacts();
        print_contacts(contacts);
    }

    void ContactCLI::print_contact(const entities::Contact& contact) const
    {
        println();
        println("ID: ", contact.id);
        println("Name: ", contact.first_name, " ", contact.last_name);
        println("Email: ", contact.email);

        if (contact.phones.empty())
        {
            println("Phones: No phones");
        }
        else
        {
            println("Phones:");
            for (const auto& phone : contact.phones)
            {
                println("  [", phone.id, "] ", phone.number);
            }
        }

        println();
    }

    void ContactCLI::print_contacts(const std::vector<entities::Contact>& contacts) const
    {
        if (contacts.empty())
        {
            println("\nNo contacts found\n");
            return;
        }

        for (const auto& contact : contacts)
        {
            print_contact(contact);
        }
    }

    std::string ContactCLI::get_input(std::string_view prompt) const
    {
        print(prompt);
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    int ContactCLI::get_int_input(std::string_view prompt) const
    {
        while (true)
        {
            const auto input = get_input(prompt);

            try
            {
                return std::stoi(input);
            }
            catch (const std::invalid_argument&)
            {
                println("\nInvalid number.\n");
            }
            catch (const std::out_of_range&)
            {
                println("\nNumber out of range.\n");
            }
        }
    }

}

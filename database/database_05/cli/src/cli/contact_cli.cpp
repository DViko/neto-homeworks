#include "cli/contact_cli.hpp"

#include <algorithm>

namespace cli
{
    using utils::IO;

    CLI::CLI(repository::IContactRepository& repo) : repository_(repo)
    {
        dispatcher_.register_command({"1", "Create tables", [this]() { create_tables_(); }});
        dispatcher_.register_command({"2", "Add contact", [this]() { insert_contact_(); }});
        dispatcher_.register_command({"3", "Update contact", [this]() { update_contact_(); }});
        dispatcher_.register_command({"4", "Remove contact", [this]() { remove_contact_(); }});
        dispatcher_.register_command({"5", "Add phone to contact", [this]() { insert_phone_(); }});
        dispatcher_.register_command({"6", "Update phone", [this]() { update_phone_(); }});
        dispatcher_.register_command({"7", "Remove phone", [this]() { remove_phone_(); }});
        dispatcher_.register_command({"8", "Find contact", [this]() { find_contact_(); }});
        dispatcher_.register_command({"9", "List contacts", [this]() { list_contacts_(); }});
        dispatcher_.register_command({"10", "Exit", [this]() { is_running_ = false; }});
        dispatcher_.register_command({"help", "Show command list", [this]() { show_menu_(); }});
    }

    void CLI::update_field_(std::string& field, std::string_view label)
    {
        const auto value = IO::read_line(std::string(label) + " [" + field + "]: ");

        if (!value.empty())
        {
            field = value;
        }
    }

    void CLI::show_menu_() const
    {
        std::vector<IO::Row> rows;

        rows.reserve(dispatcher_.commands().size());

        for (const auto& command : dispatcher_.commands())
        {
            IO::Row row;
            row.columns.push_back(IO::field(command.key, command.description));
            rows.push_back(row);
        }

        IO::print_table("COMMANDS", rows);
    }

    void CLI::run()
    {
        IO::info("Type 'help' to show command list");

        while (is_running_)
        {
            try
            {
                if (!dispatcher_.dispatch(IO::read_line("db> ")))
                {                 
                    IO::info("Unknown command. Type 'help' to show command list");
                }
            }
            catch (const std::exception& e)
            {
                IO::exception(e.what());
            }
        }
    }

    void CLI::create_tables_()
    {
        repository_.create_tables();

        IO::info("Tables created");
    }

    void CLI::insert_contact_()
    {
        entity::Contact contact
        {
            0,
            IO::read_line("\nFirst name: "),
            IO::read_line("\nLast name: "),
            IO::read_line("\nEmail: "),
            {}
        };

        if(contact.first_name.empty() || contact.last_name.empty() || contact.email.empty())
        {
            IO::info("First name, last name and email cannot be empty");
            return;
        }

        const std::string phone = IO::read_line("\nPhone (optional): ");

        if (!phone.empty())
        {
            contact.phones.push_back({0, phone});
        }

        repository_.insert_contact(contact);

        IO::info("Contact added");
    }

    void CLI::update_contact_()
    {
        const auto existing_contact = repository_.select_contact_by_id(IO::read_int("\nContact ID: "));

        if (!existing_contact)
        {
            IO::info("Contact not found");
            return;
        }

        auto contact = *existing_contact;

        IO::info("Leave fields empty to preserve current values");

        update_field_(contact.first_name, "First name");
        update_field_(contact.last_name,  "Last name");
        update_field_(contact.email,      "Email");

        repository_.update_contact(contact);

        IO::info("Contact updated");
    }

    void CLI::remove_contact_()
    {
        int id = IO::read_int("\nContact ID: ");
    
        if (!repository_.select_contact_by_id(id))
        {
            IO::info("Contact not found");
            return;
        }
        
        repository_.remove_contact(id);

        IO::info("Contact removed");
    }

    void CLI::insert_phone_()
    {
        int contact_id = IO::read_int("\nContact ID: ");

        auto contact = repository_.select_contact_by_id(contact_id);

        if (!contact)
        {
            IO::info("Contact not found");
            return;
        }
        
        std::string phone = IO::read_line("\nPhone: ");
        
        if (phone.empty())
        {
            IO::info("Phone number cannot be empty");
            return;
        }
        
        contact->phones.push_back({0, phone});
        repository_.update_contact(*contact);

        IO::info("Phone added");                        
    }

    void CLI::update_phone_()
    {
        int phone_id = IO::read_int("\nPhone ID: ");

        std::string new_phone = IO::read_line("\nNew phone: ");

        if (new_phone.empty())
        {
            IO::info("Phone number cannot be empty");
            return;
        }

        auto contact = repository_.select_contact_by_phone_id(phone_id);

        if (!contact)
        {
            IO::info("Phone not found");
            return;
        }

        auto phone_it = std::find_if(contact->phones.begin(), contact->phones.end(),
            [phone_id](const entity::Phone& p)
            {
                return p.id == phone_id;
            });

        phone_it->number = new_phone;

        repository_.update_contact(*contact);

        IO::info("Phone updated");
    }

    void CLI::remove_phone_()
    {
        int phone_id = IO::read_int("\nPhone ID: ");

        auto contact = repository_.select_contact_by_phone_id(phone_id);

        if (!contact)
        {
            IO::info("Phone not found");
            return;
        }

        auto phone_it = std::find_if(contact->phones.begin(), contact->phones.end(),
            [phone_id](const entity::Phone& p)
            {
                return p.id == phone_id;
            });

        contact->phones.erase(phone_it);

        repository_.update_contact(*contact);

        IO::info("Phone removed");
    }

    void CLI::find_contact_()
    {
        std::string term = IO::read_line("\nSearch: ");
    
        if (term.empty())
        {
            IO::info("Search term cannot be empty");
            return;
        }
        
        output_(repository_.find_contact(term));
    }

    void CLI::list_contacts_()
    {
        output_(repository_.select_contact_list());
    }


    void CLI::output_(const std::vector<entity::Contact>& contacts)
    {
        if (contacts.empty())
        {
            IO::info("No contacts found");
            return;
        }

        std::vector<IO::Row> rows;

        for (const auto& contact : contacts)
        {
            IO::Row row;

            row.columns.push_back(IO::field("ID", std::to_string(contact.id)));
            row.columns.push_back(IO::field("Name", contact.first_name + " " + contact.last_name));
            row.columns.push_back(IO::field("Email", contact.email));

            if (contact.phones.empty())
            {
                row.columns.push_back(IO::field("Phones", "none"));
            }
            else
            {
                for (const auto& phone : contact.phones)
                {
                    row.columns.push_back(IO::field("Phone[" + std::to_string(phone.id) + "]", phone.number));
                }
            }

            rows.push_back(std::move(row));
        }

        IO::print_list("CONTACTS", rows);
    }
}
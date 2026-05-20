#include "cli/contact_cli.hpp"

namespace cli
{
    using utils::ConsoleIO;

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

    void CLI::run()
    {
        ConsoleIO::write("\n\nType 'help' to show command list\n\n");

        while (is_running_)
        {
            try
            {
                if (!dispatcher_.dispatch(ConsoleIO::read_line(build_prompt_())))
                {
                    ConsoleIO::write("\n\nUnknown command. Type 'help' to show command list\n\n");
                }
            }
            catch (const std::exception& e)
            {
                ConsoleIO::write("\n\nError: ", e.what(), "\n\n");
            }
        }
    }

    std::string CLI::build_prompt_() const
    {
        if (!in_context_.empty())
        {
            return "db-cli[" + in_context_ + "]> ";
        }

        return "db-cli> ";
    }

    void CLI::update_field_(std::string& field, std::string_view label)
    {
        const auto value = ConsoleIO::read_line(std::string(label) + " [" + field + "]: ");

        if (!value.empty())
        {
            field = value;
        }
    }

    void CLI::show_menu_() const
    {
        ConsoleIO::section_begin("COMMANDS");

        for (const auto& command : dispatcher_.commands())
        {
            ConsoleIO::writef(command.key, command.description);
        }

        ConsoleIO::section_end();
    }


    void CLI::create_tables_()
    {
        repository_.create_tables();

        ConsoleIO::write("\nTables created\n\n");
    }

    void CLI::insert_contact_()
    {
        entity::Contact contact
        {
            0,
            ConsoleIO::read_line("First name: "),
            ConsoleIO::read_line("Last name: "),
            ConsoleIO::read_line("Email: ")
        };

        const std::string phone = ConsoleIO::read_line("Phone (optional): ");

        if (!phone.empty())
        {
            contact.phones.push_back({0, phone});
        }

        repository_.insert_contact(contact);

        ConsoleIO::write("\nContact added\n\n");
    }

    void CLI::update_contact_()
    {
        const auto existing_contact = repository_.select_contact_by_id(ConsoleIO::read_int("Contact ID: "));

        if (!existing_contact)
        {
            ConsoleIO::write("\nContact not found\n\n");
            return;
        }

        auto contact = *existing_contact;

        ConsoleIO::write("\nLeave fields empty to preserve current values.\n\n");

        update_field_(contact.first_name, "First name");
        update_field_(contact.last_name,  "Last name");
        update_field_(contact.email,      "Email");

        repository_.update_contact(contact);

        ConsoleIO::write("\nContact updated\n\n");
    }

    void CLI::remove_contact_()
    {
        int id = ConsoleIO::read_int("Contact ID: ");
    
        if (!repository_.select_contact_by_id(id))
        {
            ConsoleIO::write("\nContact not found\n\n");
            return;
        }
        
        repository_.remove_contact(id);

        ConsoleIO::write("\nContact removed\n\n");
    }

    void CLI::insert_phone_()
    {
        int contact_id = ConsoleIO::read_int("Contact ID: ");

        if (!repository_.select_contact_by_id(contact_id))
        {
            ConsoleIO::write("\nContact not found\n\n");
            return;
        }
        
        std::string phone = ConsoleIO::read_line("Phone: ");
        
        if (phone.empty())
        {
            ConsoleIO::write("\nPhone number cannot be empty\n\n");
            return;
        }
        
        repository_.insert_phone(contact_id, phone);
        ConsoleIO::write("\nPhone added\n\n");
    }

    void CLI::update_phone_()
    {
        
        int phone_id = ConsoleIO::read_int("Phone ID: ");

        std::string new_phone = ConsoleIO::read_line("New phone: ");

        if (new_phone.empty())
        {
            ConsoleIO::write("\nPhone number cannot be empty\n\n");
            return;
        }

        repository_.select_phone_by_id(phone_id);

        repository_.update_phone(phone_id, new_phone);

        ConsoleIO::write("\nPhone updated\n\n");
    }

    void CLI::remove_phone_()
    {
        repository_.remove_phone(ConsoleIO::read_int("Phone ID: "));
        
        ConsoleIO::write("\nPhone removed\n\n");
    }

    void CLI::find_contact_()
    {
        std::string term = ConsoleIO::read_line("Search: ");
    
        if (term.empty())
        {
            ConsoleIO::write("\nSearch term cannot be empty\n\n");
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
            ConsoleIO::write("\nNo contacts found\n\n");
            return;
        }

        ConsoleIO::section_begin("CONTACTS");

        for(const auto& contact : contacts)
        {
            auto row = ConsoleIO::make_row({
                "ID:         " + std::to_string(contact.id),
                "Name:       " + contact.first_name + " " + contact.last_name,
                "Email:      " + contact.email
            });

            if (contact.phones.empty())
            {
                row.columns.push_back({"Phone:      No phones"});
            }
            else
            {
                for (const auto& phone : contact.phones)
                {
                    row.columns.push_back({
                        "Phone[" + std::to_string(phone.id) + "]:   " + phone.number
                    });
                }
            }

            ConsoleIO::print_row(row);
            ConsoleIO::section_end();
        }
    }
}
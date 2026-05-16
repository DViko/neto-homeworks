#include "client_cli.hpp"

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <functional>

namespace cli
{
    ClientCLI::ClientCLI(repositories::ClientRepository& repo) : m_repo(repo)
    {
        register_commands();
    }

    void ClientCLI::run()
    {
        println("\nType 'help' to show command list\n");

        while (m_running)
        {
            const std::string command = get_input("\nEnter command: ");

            auto it = m_commands.find(command);

            if (it == m_commands.end())
            {
                println("\nUnknown command. Type 'help'\n");
                continue;
            }

            try
            {
                it -> second();
            }
            catch (const std::exception& e)
            {
                println("Error: ", e.what());
            }
        }
    }

    void ClientCLI::register_commands()
    {
        m_commands["1"] = [this](){ handle_create_tables(); };
        m_commands["2"] = [this](){ handle_add_client(); };
        m_commands["3"] = [this](){ handle_add_phone(); };
        m_commands["4"] = [this](){ handle_update_client(); };
        m_commands["5"] = [this](){ handle_remove_phone(); };
        m_commands["6"] = [this](){ handle_remove_client(); };
        m_commands["7"] = [this](){ handle_find_clients(); };
        m_commands["8"] = [this](){ handle_list_clients(); };
        m_commands["9"] = [this](){ m_running = false; };
        m_commands["help"] = [this](){ show_menu(); }; 
    }

    void ClientCLI::show_menu()
    {
        println(R"(

        Actions:                Commands:

        Create tables           1
        Add client              2
        Add phone to client     3
        Update client           4
        Remove phone            5
        Remove client           6
        Find clients            7
        List all clients        8
        Exit                    9

        )");
    }

    void ClientCLI::handle_create_tables()
    {
        m_repo.create_tables();

        println("\nTables created successfully\n");
    }

    void ClientCLI::handle_add_client()
    {
        entities::Client client;

        client.first_name = get_input("First name: ");
        client.last_name = get_input("Last name: ");
        client.email = get_input("Email: ");
        client.phones = get_phones_input();

        m_repo.add_client(client);

        println("\nClient added successfully\n");
    }

    void ClientCLI::handle_add_phone()
    {
        const int client_id = get_int_input("Client ID: ");
        const std::string phone = get_input("Phone: ");

        m_repo.add_phone(client_id, phone);

        println("\nPhone added successfully\n");
    }

    void ClientCLI::handle_update_client()
    {
        entities::Client client;

        client.id = get_int_input("Client ID: ");
        client.first_name = get_input("First name: ");
        client.last_name = get_input("Last name: ");
        client.email = get_input("Email: ");
        client.phones = get_phones_input();

        m_repo.update_client(client);

        println("\nClient updated successfully\n");
    }

    void ClientCLI::handle_remove_phone()
    {
        const int phone_id = get_int_input("Phone ID: ");

        m_repo.remove_phone(phone_id);

        println("\nPhone removed successfully\n");
    }

    void ClientCLI::handle_remove_client()
    {
        const int client_id = get_int_input("Client ID: ");

        m_repo.remove_client(client_id);

        println("\nClient removed successfully\n");
    }

    void ClientCLI::handle_find_clients()
    {
        const std::string term = get_input("Search: ");
        const auto clients = m_repo.find_clients(term);

        print_clients(clients);
    }

    void ClientCLI::handle_list_clients()
    {
        const auto clients = m_repo.get_all_clients();

        print_clients(clients);
    }

    void ClientCLI::print_client(const entities::Client& client)
    {
        println();
        println("ID: ", client.id);
        println("Name: ", client.first_name, " ", client.last_name);
        println("Email: ", client.email);
        std::cout << "Phones: ";

        if (client.phones.empty())
        {
            std::cout << "No phones";
        }
        else
        {
            for (size_t i = 0; i < client.phones.size(); ++i)
            {
                std::cout << client.phones[i];
                if (i + 1 < client.phones.size())
                {
                    std::cout << ", ";
                }
            }
        }

        std::cout << '\n';
    }

    void ClientCLI::print_clients(const std::vector<entities::Client>& clients)
    {
        if (clients.empty())
        {
            println("\nNo clients found\n");
            return;
        }

        for (const auto& client : clients)
        {
            print_client(client);
        }
    }

    std::string ClientCLI::get_input(const std::string& prompt)
    {
        println(prompt);
        std::string input;
        std::getline(std::cin, input);

        return input;
    }

    int ClientCLI::get_int_input(const std::string& prompt)
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

    std::vector<std::string> ClientCLI::get_phones_input()
    {
        const std::string input = get_input("Phones (Example: 123-456-7890, 098-765-4321): ");

        if (input.empty())
        {
            return {};
        }

        std::vector<std::string> phones;
        std::stringstream ss(input);
        std::string token;

        while (std::getline(ss, token, ','))
        {
            const auto start = token.find_first_not_of(" \t");
            if (start == std::string::npos) continue;
            const auto end = token.find_last_not_of(" \t");
            phones.push_back(token.substr(start, end - start + 1));
        }

        return phones;
    }
}
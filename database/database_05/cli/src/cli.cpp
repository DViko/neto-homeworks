#include "cli.hpp"

#include <iostream>
#include <string>
#include <limits>

namespace cli
{
    UserCLI::UserCLI(repositories::UserRepository& repo) : m_repo(repo)
    {
    }

    void UserCLI::run()
    {
        while (true)
        {
            show_menu();
            std::string choice = get_input("Choose an option (1-7): ");

            if (choice == "1")
            {
                handle_create_table();
            }
            else if (choice == "2")
            {
                handle_add_user();
            }
            else if (choice == "3")
            {
                handle_update_user();
            }
            else if (choice == "4")
            {
                handle_remove_user();
            }
            else if (choice == "5")
            {
                handle_list_users();
            }
            else if (choice == "6")
            {
                handle_get_user_by_id();
            }
            else if (choice == "7")
            {
                std::cout << "Exiting...\n";
                break;
            }
            else
            {
                std::cout << "Invalid choice. Please try again.\n";
            }

            std::cout << "\n";
        }
    }

    void UserCLI::show_menu()
    {
        std::cout << "=== User Management CLI ===\n";
        std::cout << "1. Create users table\n";
        std::cout << "2. Add user\n";
        std::cout << "3. Update user\n";
        std::cout << "4. Remove user\n";
        std::cout << "5. List all users\n";
        std::cout << "6. Get user by ID\n";
        std::cout << "7. Exit\n";
        std::cout << "===========================\n";
    }

    void UserCLI::handle_create_table()
    {
        try
        {
            m_repo.create_table();
            std::cout << "Users table created successfully.\n";
        }
        catch (const std::exception& e)
        {
            std::cout << "Error creating table: " << e.what() << "\n";
        }
    }

    void UserCLI::handle_add_user()
    {
        std::string name = get_input("Enter user name: ");
        entities::User user{0, name};

        try
        {
            m_repo.add(user);
            std::cout << "User added successfully.\n";
        }
        catch (const std::exception& e)
        {
            std::cout << "Error adding user: " << e.what() << "\n";
        }
    }

    void UserCLI::handle_update_user()
    {
        int id = get_int_input("Enter user ID to update: ");
        std::string name = get_input("Enter new name: ");
        entities::User user{id, name};

        try
        {
            m_repo.update(user);
            std::cout << "User updated successfully.\n";
        }
        catch (const std::exception& e)
        {
            std::cout << "Error updating user: " << e.what() << "\n";
        }
    }

    void UserCLI::handle_remove_user()
    {
        int id = get_int_input("Enter user ID to remove: ");

        try
        {
            m_repo.remove(id);
            std::cout << "User removed successfully.\n";
        }
        catch (const std::exception& e)
        {
            std::cout << "Error removing user: " << e.what() << "\n";
        }
    }

    void UserCLI::handle_list_users()
    {
        try
        {
            auto users = m_repo.get_all();
            if (users.empty())
            {
                std::cout << "No users found.\n";
                return;
            }

            std::cout << "Users:\n";
            for (const auto& user : users)
            {
                std::cout << "ID: " << user.id << ", Name: " << user.name << "\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Error listing users: " << e.what() << "\n";
        }
    }

    void UserCLI::handle_get_user_by_id()
    {
        int id = get_int_input("Enter user ID: ");

        try
        {
            auto user_opt = m_repo.get_by_id(id);
            if (user_opt)
            {
                const auto& user = *user_opt;
                std::cout << "User found - ID: " << user.id << ", Name: " << user.name << "\n";
            }
            else
            {
                std::cout << "User with ID " << id << " not found.\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Error getting user: " << e.what() << "\n";
        }
    }

    std::string UserCLI::get_input(const std::string& prompt)
    {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    int UserCLI::get_int_input(const std::string& prompt)
    {
        while (true)
        {
            std::string input = get_input(prompt);
            try
            {
                return std::stoi(input);
            }
            catch (const std::exception&)
            {
                std::cout << "Invalid input. Please enter a number.\n";
            }
        }
    }
}
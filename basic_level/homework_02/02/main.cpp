#include <iostream>

struct User
{
    unsigned int account;
    double balance;
    char name[30];
};

void UpdateUser(User& user);
void PrintInfo(const User& user);

int main()
{
    User user { 0, 0.0, "def" };

    UpdateUser(user);

    PrintInfo(user);
    
    return EXIT_SUCCESS;
}

void UpdateUser(User& user)
{
    std::cout << "Inter new bank account: ";
    std::cin >> user.account;

    std::cout << "Inter new name: ";
    std::cin >> user.name;

    std::cout << "Inter balance: ";
    std::cin >> user.balance;
    
    std::cout << "Inter new balance: ";
    std::cin >> user.balance;
}

void PrintInfo(const User& user)
{
    std::cout << "User Information: " << user.name << ", " << user.account << ", " << user.balance << std::endl;
}
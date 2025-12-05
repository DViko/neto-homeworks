#include <iostream>
#include <string>
#include <format>

int main()
{
    std::string name {}, surname {};

    std::cout << "Insert Your name: ";
    std::getline(std::cin, name);

    std::cout << "Insert Your surname: ";
    std::getline(std::cin, surname);

    std::cout << std::format("Hello, {} {} !\n", name, surname);

    return EXIT_SUCCESS;
}


#include "Leaver.hpp"
#include <string>
#include <iostream>


int main()
{
    std::string name;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    SayGoodbye(name.data(), name.size());

    return EXIT_SUCCESS;
}
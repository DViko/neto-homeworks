#include "Greeter.hpp"
#include <iostream>
#include <string>

int main()
{
    std::string name;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    Greeter greeter;
    
    greeter.SayHello(name);

    return EXIT_SUCCESS;
}
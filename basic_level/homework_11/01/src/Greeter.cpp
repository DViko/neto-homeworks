#include "Greeter.hpp"
#include <iostream>

void Greeter::SayHello(std::string name) const
{
    std::cout << "Hello, " << name << "!\n";
}
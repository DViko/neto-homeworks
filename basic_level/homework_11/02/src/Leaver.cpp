#include "Leaver.hpp"
#include <iostream>


extern "C" void SayGoodbye(const char* string, size_t length) 
{
    Leaver leaver;
    leaver.SayGoodbye(string, length);
}

void Leaver::SayGoodbye(const char* string, size_t length) const
{
    std::cout << "Goodbye, " << std::string_view(string, length) << "!\n";
}
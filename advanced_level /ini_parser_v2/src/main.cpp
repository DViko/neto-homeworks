#include <iostream>
#include "Parser.hpp"

int main()
{
    Parser parser;

    if (!parser.load("../files/config.ini"))
    {
        std::cerr << "Failed to load file\n";
        return EXIT_FAILURE;
    }

    std::cout << "Server host: " << parser.get("server", "host") << '\n';
    std::cout << "Server port: " << parser.get("server", "port") << '\n';

    return EXIT_SUCCESS;
}
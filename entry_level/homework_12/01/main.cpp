#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string buffer {};
    std::ifstream file("file.txt");

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open the file.\n";
        return EXIT_FAILURE;
    }

    while (file >> buffer) 
    {
        std::cout << buffer << std::endl;
    }

    file.close();

    return EXIT_SUCCESS;
}
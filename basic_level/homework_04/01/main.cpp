#include <iostream>
#include <fstream>
#include "AddressFormat.hpp"

int main()
{
    AddressFormat address_format;

    std::string input_file_path {"files/input.txt"};
    std::string output_file_path {"files/output.txt"};

    address_format.SetTargetFilesPath(input_file_path, output_file_path);

    try
    {
        address_format.Format();
    }
    catch(const std::exception& error)
    {
        std::cerr << error.what() << '\n';

        return EXIT_FAILURE;
    }

    std::cout << "Addresses formatted successfully." << std::endl;

    return EXIT_SUCCESS;
}
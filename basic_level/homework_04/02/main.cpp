#include <iostream>
#include <fstream>
#include "AddressSort.hpp"

int main()
{
    AddressSort address_sort;

    std::string input_file_path {"files/input.txt"};
    std::string output_file_path {"files/output.txt"};

    address_sort.SetTargetFilesPath(input_file_path, output_file_path);

    try
    {
        address_sort.FormatAndSort(true);
    }
    catch(const std::exception& error)
    {
        std::cerr << error.what() << '\n';

        return EXIT_FAILURE;
    }

    std::cout << "Addresses formatted and sorted successfully." << std::endl;

    return EXIT_SUCCESS;
}
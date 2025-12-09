#pragma once
#include <string>
#include <vector>

struct Item
{
    std::string city {};
    std::string street {};
    unsigned short house_number {};
    unsigned short apartment_number {};
};

class AddressSort
{
    private:

        std::string _input_file_path {};
        std::string _output_file_path {};

        std::vector<Item> _items {};

        bool ReadFile(std::string path);
        bool WriteFile(std::string path);
        void SortByAlphabet();

    public:

         /**
         * @brief Sets paths for input and output files
         * @param input_file Path to the input file.
         * @param output_file Path to the output file.
         */
        void SetTargetFilesPath(std::string input_file, std::string output_file);

        /**
         * @brief Format and sort the addresses alphabetically from the input file and writes to the output file.
         * @param if_sort Indicates whether to sort the addresses alphabetically.
         */
        void FormatAndSort(bool if_sort);
};
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

class AddressFormat
{
    private:

        std::string _input_file_path {};
        std::string _output_file_path {};

        std::vector<Item> _items {};

        bool ReadFile(std::string path);
        bool WriteFile(std::string path);

    public:

         /**
         * @brief Sets paths for input and output files
         * @param input_file Path to the input file.
         * @param output_file Path to the output file.
         */
        void SetTargetFilesPath(std::string input_file, std::string output_file);

        /**
         * @brief Formats the text from the input file and writes to the output file.
         */
        void Format();
};
#pragma once
#include <string>

class TextFormatting 
{
    private:
        std::string _input_file_path {};
        std::string _output_file_path {};

        bool ReadFileFromDirectory(std::string path);
        bool WriteFileToDirectory(std::string path);

    public:

        bool SetInputFilePath(std::string file_path);
        bool SetOutputFilePath(std::string file_path);

        bool FormatTextFile();
};
#include "TextFormatting.hpp"
#include <fstream>
#include <string>


bool TextFormatting::ReadFileFromDirectory(std::string path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        return false;
    }
    return true;
}

bool TextFormatting::WriteFileToDirectory(std::string path)
{
    std::ofstream file(path);

    if (!file.is_open())
    {
        return false;
    }
    return true;
}

bool TextFormatting::SetInputFilePath(std::string file_path)
{
    if (file_path.empty())
    {
        return false;
    }

    _input_file_path = std::string(file_path);
    return true;
}

bool TextFormatting::SetOutputFilePath(std::string file_path)
{
    if (file_path.empty())
    {
        return false;
    }

    _output_file_path = std::string(file_path);
    return true;
}

bool TextFormatting::FormatTextFile()
{
    ReadFileFromDirectory(_input_file_path.c_str());
    return true;
}
#include <fstream>
#include <string>
#include <limits>
#include "AddressFormat.hpp"


bool AddressFormat::ReadFile(std::string path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        return false;
    }

    size_t count {};

    file >> count;
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    _items.clear();
    _items.reserve(count);

    for (size_t i {}; i < count; i ++)
    {
        Item item;

        std::getline(file, item.city);
        std::getline(file, item.street);

        file >> item.house_number;
        file >> item.apartment_number;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        _items.push_back(item);
    }

    return true;
}

bool AddressFormat::WriteFile(std::string path)
{
    std::ofstream file(path);

    if (!file.is_open())
    {
        return false;
    }

    file << _items.size() << '\n';

    for (size_t i { _items.size() }; i -- > 0;)
    {   
        file << _items[i].city << ", ";
        file << _items[i].street << ", ";
        file << _items[i].house_number << ", ";
        file << _items[i].apartment_number << '\n';
    }

    return true;
}

void AddressFormat::SetTargetFilesPath(std::string input_file, std::string output_file)
{
    _input_file_path = input_file;
    _output_file_path = output_file;
}

void AddressFormat::Format()
{
    if (!ReadFile(_input_file_path))
    {
        throw std::runtime_error("The input file could not be read.");
    }

    if (!WriteFile(_output_file_path))
    {
        throw std::runtime_error("The output file could not be written.");
    }
}
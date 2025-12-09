#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include "AddressSort.hpp"


bool AddressSort::ReadFile(std::string path)
{
    std::ifstream input_file(path);

    if (!input_file.is_open())
    {
        return false;
    }

    size_t count {};

    input_file >> count;
    input_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    _items.clear();
    _items.reserve(count);

    for (size_t i {}; i < count; i ++)
    {
        Item item;

        std::getline(input_file, item.city);
        std::getline(input_file, item.street);

        input_file >> item.house_number >> item.apartment_number;
        input_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        _items.push_back(item);
    }

    return true;
}

bool AddressSort::WriteFile(std::string path)
{
    std::ofstream output_file(path);

    if (!output_file.is_open())
    {
        return false;
    }

    output_file << _items.size() << '\n';

    for (size_t i {}; i < _items.size(); i ++)
    {
        output_file << _items[i].city << ", ";
        output_file << _items[i].street << ", ";
        output_file << _items[i].house_number << ", ";
        output_file << _items[i].apartment_number << '\n';
    }

    return true;
}

void AddressSort::SortByAlphabet()
{
    std::sort(_items.begin(), _items.end(),

        [](const Item& item_a, const Item& item_b)
        {
            return item_a.city < item_b.city;
        }
    );
}

void AddressSort::SetTargetFilesPath(std::string input_file, std::string output_file)
{
    _input_file_path = input_file;
    _output_file_path = output_file;
}

void AddressSort::FormatAndSort(bool if_sort)
{
    if (!ReadFile(_input_file_path))
    {
        throw std::runtime_error("The input file could not be read.");
    }

    if (if_sort)
    {
        SortByAlphabet();
    }

    if (!WriteFile(_output_file_path))
    {
        throw std::runtime_error("The output file could not be written.");
    }
}
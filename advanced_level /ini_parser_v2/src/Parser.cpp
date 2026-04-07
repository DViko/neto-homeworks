#include "Parser.hpp"

#include <fstream>
#include <sstream>

bool Parser::load(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
        return false;

    std::string line;
    std::string current_section;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        if (line.front() == '[' && line.back() == ']')
        {
            current_section = line.substr(1, line.size() - 2);
        }
        else
        {
            auto pos = line.find('=');
            
            if (pos == std::string::npos)
                continue;

            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            data[current_section][key] = value;
        }
    }

    return true;
}

std::string Parser::get(const std::string& section, const std::string& key) const
{
    return data.at(section).at(key);
}
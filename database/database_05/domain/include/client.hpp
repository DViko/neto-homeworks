#pragma once

#include <string>
#include <vector>

namespace entities
{
    struct Client
    {
        int id{};
        std::string first_name;
        std::string last_name;
        std::string email;
        std::vector<std::string> phones;
    };
}
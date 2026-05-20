#pragma once

#include <string>
#include <vector>

namespace entity
{
    struct Phone
    {
        int id;
        std::string number;
    };

    struct Contact
    {
        int id;
        std::string first_name;
        std::string last_name;
        std::string email;
        std::vector<Phone> phones;
    };
}
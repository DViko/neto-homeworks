#include <iostream>
#include <cstdlib>
#include <cstring>

unsigned short simple_string_hash(const char *str)
{

    unsigned short hash{0};

    while (*str != '\0')
    {
        hash += static_cast<unsigned char>(*str);
        ++str;
    }

    return hash;
}

int main()
{
    const int buffer{256};
    char str[buffer];

    while (true)
    {
        std::cout << "Enter a string (or 'exit' to quit): ";

        std::cin.getline(str, buffer);

        std::cout << "Naive hash of the string \"" << str << "\": " << simple_string_hash(str) << '\n';

        if (!std::strcmp(str, "exit"))
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}
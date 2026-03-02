#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdint>

uint64_t real_string_hash(const char *str, uint64_t p, uint64_t n)
{
    uint64_t hash{0}, p_pow{1};

    while (*str != '\0')
    {
        hash = (hash + static_cast<unsigned char>(*str) * p_pow) % n;
        p_pow = (p_pow * p) % n;
        ++str;
    }

    return hash;
}

int main()
{
    const int buffer{256};
    char str[buffer];

    uint64_t p{}, n{};

    std::cout << "Enter a prime number p: ";
    std::cin >> p;

    std::cout << "Enter a large number n: ";
    std::cin >> n;

    std::cin.ignore(10000, '\n');

    while (true)
    {
        std::cout << "Enter a string (or 'exit' to quit): ";

        std::cin.getline(str, buffer);

        std::cout << "Hash of the string \"" << str << "\": " << real_string_hash(str, p, n) << '\n';

        if (!std::strcmp(str, "exit"))
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}

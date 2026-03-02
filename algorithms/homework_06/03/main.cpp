#include <iostream>
#include <cstdlib>
#include <cstring>

constexpr long long P{31};
constexpr long long M{1000000007};

int find_substring_light_rabin_karp(const char *text, const char *pattern);

int main()
{
    constexpr int buffer{256};

    char text[buffer], pattern[buffer];

    std::cout << "Enter the text: ";
    std::cin.getline(text, buffer);

    while (true)
    {
        std::cout << "Enter substring to find: ";
        std::cin.getline(pattern, buffer);

        int index{find_substring_light_rabin_karp(text, pattern)};

        if (index >= 0)
        {
            std::cout << "Substring " << pattern << " found at index " << index << '\n';
        }
        else
        {
            std::cout << "Substring " << pattern << " not found\n";
        }

        if (!strcmp(pattern, "exit"))
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}

long long string_hash(const char *str, size_t len)
{
    long long hash{0}, p_pow{1};

    for (size_t i{}; i < len; i++)
    {
        hash = (hash + static_cast<unsigned char>(str[i]) * p_pow) % M;
        p_pow = (p_pow * P) % M;
    }

    return hash;
}

int find_substring_light_rabin_karp(const char *text, const char *pattern)
{
    size_t text_len{strlen(text)}, pattern_len{strlen(pattern)};

    if (pattern_len > text_len)
    {
        return -1;
    }

    long long pattern_hash{string_hash(pattern, pattern_len)};

    for (size_t i{}; i <= text_len - pattern_len; i++)
    {
        long long current_hash{string_hash(text + i, pattern_len)};

        if (current_hash == pattern_hash && strncmp(text + i, pattern, pattern_len) == 0)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}
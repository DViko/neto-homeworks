#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

int main()
{
    std::string input{ "Hello world!!" };

    std::unordered_map<unsigned char, int> freq{};

    for (unsigned char c : input)
    {
        ++freq[c];
    }

    std::vector<std::pair<unsigned char, int>> data(freq.begin(), freq.end());

    std::sort(data.begin(), data.end(),

        [](const auto& a, const auto& b)
        {
            if (a.second != b.second)
            {
                return a.second > b.second;
            }
            return a.first < b.first;
        }
    );

    std::cout << "[INPUT]: " << input << "\n";
    std::cout << "[OUTPUT]:\n";

    for (const auto& [ch, count] : data)
    {
        std::cout << static_cast<char>(ch) << ": " << count << '\n';
    }
}
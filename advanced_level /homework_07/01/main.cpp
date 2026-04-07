#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> make_unique(std::vector<int> input)
{
    std::sort(input.begin(), input.end());

    input.erase(std::unique(input.begin(), input.end()), input.end());

    return input;
}

int main()
{
    std::vector<int> input{ 1, 1, 2, 5, 6, 1, 2, 4 };

    auto result { make_unique(input) };

    std::cout << "[IN]: ";

    for (int x : input)
    {
        std::cout << x << " ";
    }

    std::cout << "\n[OUT]: ";
    for (int x : result)
    {
        std::cout << x << " ";
    }

    std::cout << "\n";
}
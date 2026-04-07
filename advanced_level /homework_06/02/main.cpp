#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

int main()
{
    int size{};

    std::cout << "[IN]: \n";
    std::cin >> size;

    std::vector<int> input(size);

    for (int& x : input)
    {
        std::cin >> x;
    }

    std::unordered_set<int> uniq(input.begin(), input.end());

    std::vector<int> result(uniq.begin(), uniq.end());

    std::sort(result.begin(), result.end(), std::greater<>());

    std::cout << "[OUT]:\n";

    for (int x : result)
    {
        std::cout << x << "\n";
    }
}
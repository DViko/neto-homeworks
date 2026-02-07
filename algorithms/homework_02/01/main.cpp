#include <iostream>
#include <vector>

long long search_fibonacci(unsigned short number, std::vector<long long> &memo)
{
    if (number <= 1)
    {
        return number;
    }
    if (memo[number] != -1)
    {
        return memo[number];
    }

    memo[number] = search_fibonacci(number - 1, memo) + search_fibonacci(number - 2, memo);

    return memo[number];
}

int main()
{
    unsigned short number;

    std::cout << "Insert number (0 <= number <= 92): ";
    std::cin >> number;

    if (number < 0 || number > 92)
    {
        std::cout << "Error: number must be from 0 to 92!" << std::endl;

        return EXIT_FAILURE;
    }

    std::vector<long long> memo(number + 1, -1);

    std::cout << "Result(" << number << ") = " << search_fibonacci(number, memo) << '\n';

    return EXIT_SUCCESS;
}

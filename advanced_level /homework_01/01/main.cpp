#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

void print_vector(const std::vector<int>& vector, const char* label);

int main()
{
    std::vector<int> vector{4, 7, 9, 14, 12};

    print_vector(vector, "Original vector: ");

    std::for_each(vector.begin(), vector.end(),
    
        [](int &x) { if (x % 2 != 0) x *= 3; }
    );

    print_vector(vector, "Transformed vector: ");

    return EXIT_SUCCESS;
}

void print_vector(const std::vector<int>& vector, const char* label)
{
    std::cout << label;

    for (int x : vector)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";
}
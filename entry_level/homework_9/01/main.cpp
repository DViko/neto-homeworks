#include <iostream>

void print(const int array[], int size);


int main()
{
    int array_a[5] {34, 28, -3, 14, -95},
        array_b[7] {10, 20, 30, 40, 50, 132, 217},
        array_c[3] {-72, 68, -51};

    print(array_a, std::size(array_a));
    print(array_b, std::size(array_b));
    print(array_c, std::size(array_c));

    return EXIT_SUCCESS;
}

void print(const int array[], int size)
{
    for (int i {0}; i < size; i ++)
    {
        std::cout << array[i] << (i < size - 1 ? ", " : "\n");
    }
}
#include <iostream>
#include <format>

int main() {

    int array[10]{68, 12, 8, 43, 75, 90, 11, 23, 56, 34};
    const int SIZE = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < SIZE; i ++)
        std::cout << std::format("{}{}", array[i], (i < SIZE - 1 ? ", " : "\n"));

    return EXIT_SUCCESS;
}
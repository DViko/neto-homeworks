#include <iostream>
#include <format>

int main() {

    int array[10]{65, 17, -42, 99, -23, 8, 76, 54, 31, 88};
    int min{array[0]}, max{array[0]};

    const int SIZE = sizeof(array) / sizeof(array[0]);


    std::cout << "Source array: ";

    for (int i = 1; i < SIZE; i ++) {

        if (array[i] < min) min = array[i];
        if (array[i] > max) max = array[i];

        std::cout << std::format("{}{}", array[i], (i < SIZE - 1 ? ", " : "\n"));
    }

    std::cout << std::format("Min value: {}  Max value: {} \n", min, max);
    
    return EXIT_SUCCESS;
}
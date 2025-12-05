#include <iostream>
#include <algorithm>

std::pair<int, int> getMinMax(const int array[], int size);

int main() {

    int array[10]{68, 12, 8, 43, 75, 90, 11, 23, 56, 34};
    int SIZE{sizeof(array) / sizeof(array[0])};

    std::cout << "Array: ";

    for (int i = 1; i < SIZE; ++i)

        std::cout << array[i] << " ";

    std::cout << std::endl;

    auto [min, max] = getMinMax(array, SIZE);

    std::cout << "Min: " << min << " "<< "Max: " << max << std::endl;

    return EXIT_SUCCESS;
}

std::pair<int, int> getMinMax(const int array[], int size) {

    auto [min, max] = std::minmax_element(array, array + size);

    return {*min, *max};
}
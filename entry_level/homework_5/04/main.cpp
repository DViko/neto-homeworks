#include <iostream>
#include <functional>
#include <format>

void reverseBubbleSort(int array[], int size, std::function<bool(int, int)> cmp);
void printArray(int array[], int size);

int main() {

    int array[10]{64, 34, 25, 12, -22, 11, 90, -3, 1, 42};
    const int SIZE{sizeof(array) / sizeof(array[0])};

    std::cout << "Source array: ";

    printArray(array, SIZE);

    std::cout << "Sorted array: ";

    reverseBubbleSort(array, SIZE, [](int a, int b) { return a < b; });

    printArray(array, SIZE);

    return EXIT_SUCCESS;
}

void reverseBubbleSort(int array[], int size, std::function<bool(int, int)> cmp) {

    for (int i = 0; i < size - 1; i ++) {

        bool swapped{false};

        for (int j = size - 1; j > i; j --) {

            if (cmp(array[j], array[ j - 1 ])) {

                std::swap(array[j], array[ j - 1 ]);

                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

void printArray(int array[], int size) {

    for (int i = 0; i < size; i ++) {

        std::cout << std::format("{}{}", array[i], (i < size - 1 ? ", " : "\n"));
    }
}
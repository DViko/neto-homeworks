#include <iostream>

void reverseBubbleSort(int array[], int size);
void printArray(const int array[], int size);

int main() {

    int array[10]{45, -32, 11, 95, -81, 3, 54, 73, 5, 19};
    constexpr int SIZE{sizeof(array) / sizeof(array[0])};

    std::cout << "Source array: ";

    printArray(array, SIZE);

    std::cout << "Reverse bubble sort: ";

    reverseBubbleSort(array, SIZE);

    printArray(array, SIZE);

    return EXIT_SUCCESS;
}

void reverseBubbleSort(int array[], int size) {

    for (int i = 0; i < size - 1; i ++) {

        bool swapped{false};

        for (int j = size - 1; j > i; j --) {

            if (array[j] < array[ j - 1 ]) {

                int buffer{array[j]};

                array[j] = array[ j - 1 ];
                array[ j - 1 ] = buffer;

                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

void printArray(const int array[], int size) {
    
    for (int i = 0; i < size; i ++) {

        std::cout << array[i];

        if (i < size - 1) std::cout << " ";
    }

    std::cout << "\n";
}
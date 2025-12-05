#include <iostream>

void reverse(int* begin, int* end);
void swap(int* x, int* y);
void print (const int array[], int size);

int main()
{
    int numbers[9] {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const int SIZE {sizeof(numbers) / sizeof(numbers[0])};

    print(numbers, SIZE);
    reverse(numbers, numbers + SIZE - 1);
    print(numbers, SIZE);

    return EXIT_SUCCESS;
}

void reverse(int* begin, int* end)
{
    while (begin < end)
    {
        swap(begin ++, end --);
    }
}

void swap(int* x, int* y)
{
    int buff {*x};

    *x = *y;
    *y = buff;
}

void print (const int array[], int size)
{
    for (int i {0}; i < size; i ++)
    {
        std::cout << array[i] << (i < size - 1 ? ", " : "\n");
    }
}

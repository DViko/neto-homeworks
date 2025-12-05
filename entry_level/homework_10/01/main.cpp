#include <iostream>

bool ReadValue(int& value);
bool CreateAndFillArray(int*& array, int size);
void PrintArray(const int* array, int size);

int main()
{
    int size {0};
    int* array {nullptr};

    std::cout << "Enter the size of the array: ";

    if(ReadValue(size) && CreateAndFillArray(array, size))
    {
        PrintArray(array, size);

        delete[] array;
        array = nullptr;

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

bool ReadValue(int& value)
{
    if (!(std::cin >> value))
    {
        std::cout << "Invalid input: not an integer.\n";

        return false;
    }

    return true;
}

bool CreateAndFillArray(int*& array, int size)
{
    if (size <= 0)
    {
        std::cout << "Error: Array size must be a positive integer and greater than zero.\n";

        return false;
    }

    try
    {
        array = new int[size];
    }
    catch (const std::bad_alloc& error)
    {
        std::cout << "Error: Memory allocation failed: " << error.what() << "\n";

        return false;
    }

    for (int i {0}; i < size; i ++)
    {
        std::cout << "Enter element " << i + 1 << ": ";

        if(!ReadValue(array[i]))
        {
            delete[] array;
            array = nullptr;

            return false;
        }
    }

    return true;
}

void PrintArray(const int* array, int size)
{
    std::cout << "Array elements: ";

    for (int i {0}; i < size; i ++)
    {
        std::cout << array[i] << (i < size - 1 ? ", " : "\n");
    }
}
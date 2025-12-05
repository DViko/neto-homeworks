#include <iostream>

bool    ReadValue(int& value);
double* CreateAndFillArray(double* array, int size);
void    PrintArray(double* array, int size);
void    DeleteArray(double*& array);

int main()
{
    int size {0};
    double* array {nullptr};

    std::cout << "Enter the size of the array: ";

    if (ReadValue(size))
    {
        array = CreateAndFillArray(array, size);

        if (array == nullptr)
        {
            return EXIT_FAILURE;
        }

        PrintArray(array, size);
        DeleteArray(array);

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

bool ReadValue(int& value)
{
    if (!(std::cin >> value) || value <= 0)
    {
        std::cout << "Error: Array size must be a positive integer and greater than zero.\n";

        return false;
    }

    return true;
}

double* CreateAndFillArray(double* array, int size)
{
    try
    {
        return new double[size]();
    }
    catch (const std::bad_alloc& error)
    {
        std::cout << "Error: Memory allocation failed: " << error.what() << "\n";

        return nullptr;
    }
}

void PrintArray(double* array, int size)
{
    std::cout << "Array elements: ";

    for (int i {0}; i < size; i ++)
    {
        std::cout << array[i] << (i < size - 1 ? ", " : "\n");
    }
}

void DeleteArray(double*& array)
{
    if (array != nullptr)
    {
        delete[] array;
        array = nullptr;
    }
}
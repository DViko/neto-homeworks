#include <iostream>
#include <iomanip>
#include <limits>

// Two-dimensional array in one-dimensional representation

int* CreateTwoDimArray(int rows, int cols);
void FillTwoDimArray(int* array, int rows, int cols);
void PrintTwoDimArray(const int* array, int rows, int cols);
void DeleteTwoDimArray(int*& array);


int main()
{
    int rows {0}, cols {0};
    int* array {nullptr};

    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    
    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    array = CreateTwoDimArray(rows, cols);

    if (array == nullptr)
    {
        return EXIT_FAILURE;
    }

    FillTwoDimArray(array, rows, cols);
    PrintTwoDimArray(array, rows, cols);
    DeleteTwoDimArray(array);

    return EXIT_SUCCESS;
}

int* CreateTwoDimArray(int rows, int cols)
{
    try
    {
        return new int[rows * cols];
    }
    catch (const std::bad_alloc& error)
    {
        std::cout << "Error: Memory allocation failed: " << error.what() << "\n";

        return nullptr;
    }
}

void FillTwoDimArray(int* array, int rows, int cols)
{
    for (int row {0}; row < rows; row++)
    {
        for (int col {0}; col < cols; col++)
        {
            array[row * cols + col] = (row + 1) * (col + 1);
        }
    }
}

void PrintTwoDimArray(const int* array, int rows, int cols)
{
    int cell_width = std::to_string(rows * cols).length() + 2;

    for (int row {0}; row < rows; row++)
    {
        for (int col {0}; col < cols; col++)
        {
            std::cout << std::setw(cell_width) << array[row * cols + col];
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

void DeleteTwoDimArray(int*& array)
{
    delete[] array;
    array = nullptr;
}
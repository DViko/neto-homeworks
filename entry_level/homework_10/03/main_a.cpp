#include <iostream>
#include <iomanip>


int** CreateTwoDimArray(int rows, int cols);
void FillTwoDimArray(int** array, int rows, int cols);
void PrintTwoDimArray(int** array, int rows, int cols);
void DeleteTwoDimArray(int** array, int rows);


int main()
{
    int cols {0}, rows {0};
    int** array {nullptr};

    std::cout << "Enter number of rows: ";
    std::cin >> rows;

    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    if (cols <= 0 || rows <= 0)
    {
        std::cout << "Error: Number of rows and columns must be positive integers greater than zero.\n";

        return EXIT_FAILURE;
    }

    array = CreateTwoDimArray(rows, cols);

    if (array == nullptr)
    {
        return EXIT_FAILURE;
    }

    FillTwoDimArray(array, rows, cols);
    PrintTwoDimArray(array, rows, cols);

    DeleteTwoDimArray(array, rows);

    return EXIT_SUCCESS;
}

int** CreateTwoDimArray(int rows, int cols)
{
    try
    {
        int** array = new int*[rows]();
        
        for (int row {0}; row < rows; row++)
        {
            array[row] = new int[cols]();
        }

        return array;
    }
    catch (const std::bad_alloc& error)
    {
        std::cout << "Error: Memory allocation failed: " << error.what() << "\n";

        return nullptr;
    }
}

void FillTwoDimArray(int** array, int rows, int cols)
{
    for (int row {0}; row < rows; row++)
    {
        for (int col {0}; col < cols; col++)
        {
            array[row][col] = (row + 1) * (col + 1);
        }
    }
}

void PrintTwoDimArray(int** array, int rows, int cols)
{
    int cell_width = std::to_string(rows * cols).length() + 2;

    for (int row {0}; row < rows; row++)
    {
        for (int col {0}; col < cols; col++)
        {
            std::cout << std::setw(cell_width) << array[row][col];
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

void DeleteTwoDimArray(int** array, int rows)
{
    for (int row {0}; row < rows; row++)
    {
        delete[] array[row];
    }
    
    delete[] array;
}
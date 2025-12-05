#include <iostream>
#include <fstream>

int main()
{
    int cols { 0 }, rows { 0 };
    int** matrix { nullptr };

    std::ifstream source ("in.txt");

    if (!source.is_open())
    {
        std::cerr << "Error: Could not open the file.\n";
        return EXIT_FAILURE;
    }

    source >> rows >> cols;
    matrix = new int* [rows]();

    for (int row {}; row < rows; row ++)
    {
        matrix[row] = new int [cols]();
    }

    for (int row {}; row < rows; row ++)
    {
        for (int col {}; col < cols; col ++)
        {
            source >> matrix[row][col];
        }
    }

    source.close();

    for (int row {}; row < rows; row ++)
    {
        for (int col { cols - 1 }; col >= 0; col --)
        {
            std::cout << matrix[row][col] << (col == 0 ? "" : ", ");;
        }
        std::cout << '\n';
    }

    for (int row {}; row < rows; row ++)
    {
        delete [] matrix[row];
    }

    delete[] matrix;
    matrix = nullptr;

    return EXIT_SUCCESS;
}


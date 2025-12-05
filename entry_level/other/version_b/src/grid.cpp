#include <vector>
#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <grid.hpp>

namespace Grid
{

    Data Create(int width, int height, int cell_size)
    {
        Data grid;
        grid.rows = height / cell_size;
        grid.columns = width / cell_size;
        grid.cell_size = cell_size;

        grid.cells = std::vector<std::vector<int>>(grid.rows, std::vector<int>(grid.columns, 0));
        return grid;
    }

    bool IsBounds(const Data& grid, int row, int column)
    {
        return row >= 0 && row < grid.rows && column >= 0 && column < grid.columns;
    }

    void SetCellValue(Data& grid, int row, int column, int value)
    {
        if (IsBounds(grid, row, column))
        {
            grid.cells[row][column] = value;
        }
    }

    int GetCellValue(const Data& grid, int row, int column)
    {
        if (IsBounds(grid, row, column))
        {
            return grid.cells[row][column];
        }
        return 0;
    }

    void FillRandom(Data& grid, float density = 0.2f)
    {
        for (int i = 0; i < grid.rows; i++)
        {
            for (int j = 0; j < grid.columns; j++)
            {
                grid.cells[i][j] = (static_cast<float>(std::rand()) / RAND_MAX < density);
            }
        }
    }

    void Draw(const Data& grid)
    {
        for (int i = 0; i < grid.rows; i++)
        {
            for (int j = 0; j < grid.columns; j++)
            {
                if (grid.cells[i][j])
                {
                    Color color = grid.cells[i][j] ? Color{0, 255, 0, 255} : Color{50, 50, 50, 255};
                    DrawRectangle(j * grid.cell_size, i * grid.cell_size, grid.cell_size - 1, grid.cell_size - 1, color);
                }
            }
        }
    }
}
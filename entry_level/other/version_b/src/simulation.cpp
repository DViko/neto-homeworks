#include <simulation.hpp>
#include <grid.hpp>

namespace Simulation
{
    constexpr int DIRECTIONS[8][2]
    {
        {-1,  0}, { 1,  0}, { 0, -1}, { 0,  1},
        {-1, -1}, {-1,  1}, { 1, -1}, { 1,  1}
    };

    Data Create(int width, int height, int cell_size)
    {
        Data data;
        data.grid = Grid::Create(width, height, cell_size);
        data.buffer = Grid::Create(width, height, cell_size);
        Grid::FillRandom(data.grid, 0.3);
        return data;
    }

    int CountLiveNeighbors(const Data& data, int row, int column)
    {
        int live_neighbors {};

        for (int i {}; i < 8; i++)
        {
            int neighbor_row { (row + DIRECTIONS[i][0] + data.grid.rows) % data.grid.rows };
            int neighbor_column { (column + DIRECTIONS[i][1] + data.grid.columns) % data.grid.columns };

            live_neighbors += data.grid.cells[neighbor_row][neighbor_column];
        }
        return live_neighbors;
    }

    void Update(Data& data)
    {
        for (int i {}; i < data.grid.rows; i++)
        {
            for (int j {}; j < data.grid.columns; j++)
            {
                int total { CountLiveNeighbors(data, i, j) };

                if (Grid::GetCellValue(data.grid, i, j))
                {
                    Grid::SetCellValue(data.buffer, i, j, (total == 2 || total == 3));
                }
                else
                {
                    Grid::SetCellValue(data.buffer, i, j, (total == 3));
                }
            }
        }

        for (int i {}; i < data.grid.rows; i++)
        {
            for (int j {}; j < data.grid.columns; j++)
            {
                Grid::SetCellValue(data.grid, i, j, Grid::GetCellValue(data.buffer, i, j));
            }
        }
    }

    void Draw(const Data& data)
    {
        Grid::Draw(data.grid);
    }

    void SetCellValue(Data& data, int row, int column, int value)
    {
        Grid::SetCellValue(data.grid, row, column, value);
    }
}
#pragma once
#include <vector>

namespace Grid
{
    struct Data
    {
        int rows {}, columns {}, cell_size {};
        std::vector<std::vector<int>> cells;
    };

    Data Create(int width, int height, int cell_size);
    bool IsBounds(const Data& grid, int row, int column);
    void SetCellValue(Data& grid, int row, int column, int value);
    int GetCellValue(const Data& grid, int row, int column);
    void FillRandom(Data& grid, float density);
    void Draw(const Data& grid);
}
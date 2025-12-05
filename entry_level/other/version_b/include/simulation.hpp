#include <grid.hpp>

namespace Simulation
{
    struct Data
    {
        Grid::Data grid;
        Grid::Data buffer;
    };

    Data Create(int width, int height, int cell_size);
    int CountLiveNeighbors(const Data& sim, int row, int column);
    void Update(Data& sim);
    void Draw(const Data& sim);
    void SetCellValue(Data& sim, int row, int column, int value);
}
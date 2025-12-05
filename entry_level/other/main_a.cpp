#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

char**  CreateGrid(int rows, int cols);
void    RandomFillGrid(char** grid, int rows, int cols, float density);
int     LookForNeighbors (char** grid, int rows, int cols, int r_current, int c_current);
void    UpdateGrid(char** grid, char** buffer, int rows, int cols);
void    UpgradeGrid(char** grid, char** buffer, int rows, int cols);
void    DrawGrid(char** grid, int rows, int cols);
void    DeleteGrid(char**& grid, int rows);


int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    constexpr short const ROWS { 10 }, COLS { 20 }, SLEEP_TIME { 150 };
    constexpr float DENSITY { 0.2 };

    char ** grid {  CreateGrid(ROWS, COLS) },
         ** buffer {  CreateGrid(ROWS, COLS) };

    if (!grid || !buffer)
    {
        DeleteGrid(grid, ROWS);
        DeleteGrid(buffer, ROWS);

        return EXIT_FAILURE;
    }

    RandomFillGrid(grid, ROWS, COLS, DENSITY);

    while (true)
    {
        std::cout << "\x1B[2J\x1B[H";;
        
        DrawGrid(grid, ROWS, COLS);
        
        UpdateGrid(grid, buffer, ROWS, COLS);
        UpgradeGrid(grid, buffer, ROWS, COLS);

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    }

    DeleteGrid(grid, ROWS);
    DeleteGrid(buffer, ROWS);

    return EXIT_SUCCESS;
}


char** CreateGrid(int rows, int cols)
{
    char** array { nullptr };

    try
    {
        array = new char* [rows] {};

        for (int i {}; i < rows; i ++)
        {
            array[i] = new char [cols]{};
        }
    }
    catch (const std::bad_alloc& error)
    {   
        std::cout << "Memory allocation failed!: " << error.what();
        return nullptr;
    }
    
    return array;
}

void RandomFillGrid(char** grid, int rows, int cols, float density)
{
    for (int i {}; i < rows; i ++)
    {
        for (int j {}; j < cols; j ++)
        {
            grid[i][j] = (static_cast<float>(std::rand()) / RAND_MAX < density) ? 1 : 0;
        }
    }
}

int LookForNeighbors(char** grid, int rows, int cols, int r_current, int c_current)
{
    int total {};

    static constexpr int dr[8] { -1, -1, -1, 0, 0, 1, 1, 1 };
    static constexpr int dc[8] { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i {}; i < 8; i ++)
    {
        total += grid[(r_current + dr[i] + rows) % rows][(c_current + dc[i] + cols) % cols];
    }

    return total;
}

void UpdateGrid(char** grid, char** buffer, int rows, int cols)
{
    for (int i {}; i < rows; i ++)
    {
        for (int j {}; j < cols; j ++)
        {
            int total { LookForNeighbors(grid, rows, cols, i, j) };

            if (grid[i][j])
            {
                buffer[i][j] = (total == 2 || total == 3);
            }
            else
            {
                buffer[i][j] = (total == 3);
            } 
        }
    }
}

void UpgradeGrid(char** grid, char** buffer, int rows, int cols)
{
    for (int i {}; i < rows; i ++)
    {
        for (int j {}; j < cols; j ++)
        {
            grid[i][j] = buffer[i][j];
        }
    }        
}

void DrawGrid(char** grid, int rows, int cols)
{
    int offset { (120 - cols) / 2 };

    for (int i {}; i < rows; i ++)
    {
        std::cout << std::string(offset, ' ');
        
        for (int j {}; j < cols; j ++)
        {
            std::cout << (grid[j][i] ? '+' : ' ');
        }

        std::cout << '\n';
    }
}

void DeleteGrid(char**& grid, int rows)
{
    if (grid)
    {
        for (int i {}; i < rows; i ++)
        {
            delete[] grid[i];
        }

        delete[] grid;
        grid = nullptr;
    }
}
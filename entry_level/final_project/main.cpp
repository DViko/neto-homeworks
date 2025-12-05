#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

struct GameState
{
    int rows {}, cols {}, generation {},
        stagnation {}, alive_total {};

    char** matrix {},
        ** buffer {};
};

constexpr int DIRECTIONS[8][2]
{
    { -1,  0 }, {  1,  0 }, { 0, -1 }, { 0,  1 },
    { -1, -1 }, { -1,  1 }, { 1, -1 }, { 1,  1 }
};

bool  CreateGameState(GameState& game);
bool  CreateInitialStateFromFile(GameState& game, const char* path_to_file);
bool  IsSameMatrix(const GameState& game);
int   LookingForNeighbors(const GameState& game, int r_current, int c_current);
void  UpdateGameState(GameState& game);
void  CountAliveCells(GameState& game);
void  DisplayGame(GameState& game);
void  DeleteGameState(GameState& game);

int main()
{
    GameState game { 0, 0, 0, 0, 0, nullptr, nullptr };

    if (!CreateInitialStateFromFile(game, "game_state.txt"))
    {
        std::cerr << "Failed to load game state\n";

        DeleteGameState(game);
        return EXIT_FAILURE;
    }

    CountAliveCells(game);
    DisplayGame(game);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    while (true)
    {
        game.generation ++;
        UpdateGameState(game);

        if (game.alive_total == 0)
        {
            std::cout << "All cells are dead. Game over.\n";
            break;
        }

        if (game.stagnation >= 2)
        {
            std::cout << "Stagnation reached. Game over.\n";
            break;
        }

        CountAliveCells(game);
        DisplayGame(game);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    DeleteGameState(game);
    return EXIT_SUCCESS;
}

bool CreateGameState(GameState& game)
{
    try
    {
        game.matrix = new char* [game.rows]();
        game.buffer = new char* [game.rows]();

        for (int row {}; row < game.rows; row ++)
        {
            game.matrix[row] = new char [game.cols]();
            game.buffer[row] = new char [game.cols]();
        }
    }
    catch (const std::bad_alloc& error)
    {
        std::cerr << "Memory allocation failed: " << error.what() << '\n';
        return false;
    }
    return true;
}

bool CreateInitialStateFromFile(GameState& game, const char* file_name)
{
    std::ifstream file(file_name);
    
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << file_name << '\n';
        return false;
    }

    file >> game.rows >> game.cols;

    if (game.rows <= 0 || game.cols <= 0)
    {
        std::cerr << "Incorrect field size: Row =" << game.rows << " Col =" << game.cols << '\n';
        return false;
    }

    if (!CreateGameState(game))
    {
        return false;
    }

    int file_row {}, file_col {};

    while (file >> file_row >> file_col)
    {
        if (file_row >= 0 && file_row < game.rows &&
            file_col >= 0 && file_col < game.cols)
        {
            game.matrix[file_row][file_col] = 1;
        }
        else
        {
            std::cerr << "\nWarning: cell (" << file_row << ", " << file_col << ") is out of bounds.\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
    }

    file.close();
    return true;
}

int LookingForNeighbors(const GameState& game, int curr_row, int curr_col)
{
    int total {};

    for (int i {}; i < 8; i ++)
    {
        int neighbor_row { curr_row + DIRECTIONS[i][0] };
        int neighbor_col { curr_col + DIRECTIONS[i][1] };

        if (neighbor_row >= 0 && neighbor_row < game.rows &&
            neighbor_col >= 0 && neighbor_col < game.cols)
        {
            total += game.matrix[neighbor_row][neighbor_col];
        }
    }

    return total;
}

bool IsSameMatrix(const GameState& game)
{
    for (int row {}; row < game.rows; row ++)
    {
        for (int col {}; col < game.cols; col ++)
        {
            if (game.matrix[row][col] != game.buffer[row][col])
            {
                return false;
            }
        }
    }
    return true;
}

void UpdateGameState(GameState& game)
{
    for (int row {}; row < game.rows; row ++)
    {
        for (int col {}; col < game.cols; col ++)
        {
            int total { LookingForNeighbors(game, row, col) };

            if (game.matrix[row][col])
            {
                game.buffer[row][col] = (total == 2 || total == 3);
            }
            else
            {
                game.buffer[row][col] = (total == 3);
            }
        }
    }

    if (IsSameMatrix(game))
    {
        game.stagnation ++;
    }     
    else
    {
        game.stagnation = 0;
    }

    for (int row {}; row < game.rows; row ++)
    {
        for (int col {}; col < game.cols; col ++)
        {
            game.matrix[row][col] = game.buffer[row][col];
        }
    }
}

void CountAliveCells(GameState& game)
{
    int total {};

    for (int row {}; row < game.rows; row ++)
    {
        for (int col {}; col < game.cols; col ++)
        {
            total += game.matrix[row][col];
        }
    }
    game.alive_total = total;
}

void DisplayGame(GameState& game)
{
    for (int row {}; row < game.rows; row ++)
    {
        for (int col {}; col < game.cols; col ++)
        {
            std::cout << (game.matrix[row][col] ? '*' : '-') << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "Generation: " << game.generation
              << " | Alive Cells: " << game.alive_total << '\n';

    std::cout << std::string(30, '-') << "\n";
}

void DeleteGameState(GameState& game)
{
    auto DeleteMatrix = [](char**& matrix, int rows)
    {
        if (!matrix)
        {
            return;
        }
        for (int row {}; row < rows; row ++)
        {
            delete[] matrix[row];
            matrix[row] = nullptr;
        }
        delete[] matrix;
        matrix = nullptr;
    };

    DeleteMatrix(game.matrix, game.rows);
    DeleteMatrix(game.buffer, game.rows);

    game.rows = game.cols = 0;
    game.generation = game.stagnation = 0;
    game.alive_total = 0;
}
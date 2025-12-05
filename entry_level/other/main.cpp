#include <iostream>
#include <fstream>
#include "raylib.h"

//g++ main.cpp -o exec -lraylib -lGL -lm

struct GameState
{
    int rows { 0 }, cols { 0 }, cell_size { 0 }, iteration { 0 };
    char** matrix { nullptr },
        ** buffer { nullptr };
};

constexpr int DIRECTIONS[8][2]
{
    {-1,  0}, { 1,  0}, { 0, -1}, { 0,  1},
    {-1, -1}, {-1,  1}, { 1, -1}, { 1,  1}
};

bool    СreateInitialStateFromFile(GameState& game, const char* path_to_file);
bool    CreateGameState(GameState& game);
int     LookingForNeighbors(GameState& game, int r_current, int c_current);
void    UpdateGameState(GameState& game);
void    UpgradeGameState(GameState& game);
void    DisplayGame(GameState& game);
void    DeleteGameState(GameState& game);

int main()
{
    GameState game { 0, 0, 8, 0, nullptr, nullptr };

    СreateInitialStateFromFile(game, "game_state.txt");
    
    InitWindow(game.rows * game.cell_size, game.cols * game.cell_size, "Cellular Automaton");
    SetTargetFPS(5);

    while (!WindowShouldClose())
    {
        UpdateGameState(game);
        UpgradeGameState(game);

        BeginDrawing();

        ClearBackground(BLACK);
        DisplayGame(game);

        EndDrawing();
    }

    DeleteGameState(game);
    CloseWindow();

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
        }

        for (int row {}; row < game.rows; row ++)
        {
            game.buffer[row] = new char [game.cols]();
        }
    }
    catch (const std::bad_alloc& error)
    {
        std::cout << "Memory allocation failed!: " << error.what();
        return false;
    }

    return true;
}

bool  СreateInitialStateFromFile(GameState& game, const char* file_name)
{
    std::ifstream file(file_name);

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << file_name << "\n";
        return false;
    }

    file >> game.rows >> game.cols;

    if (!CreateGameState(game))
    {
        return false;
    }

    int file_row {}, file_col {};

    while (file >> file_row >> file_col)
    {
        if (file_row >= 0 && file_row < game.rows && file_col >= 0 && file_col < game.cols)
        {
            game.matrix[file_row][file_col] = 1;
        }
    }

    file.close();
    return true;
}

int LookingForNeighbors(GameState& game, int r_current, int c_current)
{
    int total {};

    for (int i {}; i < 8; i++)
    {
        total += game.matrix[(r_current + DIRECTIONS[i][0] + game.rows) % game.rows]
                     [(c_current + DIRECTIONS[i][1] + game.cols) % game.cols];
    }
    return total;
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
}

void UpgradeGameState(GameState& game)
{
    for (int row {}; row < game.rows; row ++)
    {
        for (int col {}; col < game.cols; col ++)
        {
            game.matrix[row][col] = game.buffer[row][col];
        }
    }
}

void DisplayGame(GameState& game)
{
    for (int row {}; row < game.rows; row ++)
    {
        for (int col {}; col < game.cols; col ++)
        {
            if (game.matrix[row][col])
            {
                DrawRectangle(row * game.cell_size, col * game.cell_size, game.cell_size - 1, game.cell_size - 1, GREEN);
            }
            else
            {
                DrawRectangle(row * game.cell_size, col * game.cell_size, game.cell_size - 1, game.cell_size - 1, DARKGRAY);
            }
        }
    }
}

void DeleteGameState(GameState& game)
{
    for (int row {}; row < game.rows; row ++)
    {
        delete[] game.matrix[row], game.buffer[row];
    }

    delete[] game.matrix, game.buffer;
    game.matrix, game.buffer = nullptr;
}

//ToDo: Сreate a function that will write statistics to file
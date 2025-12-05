#include "raylib.h"
#include <string>
#include "grid.hpp"
#include "simulation.hpp"

int main()
{
    const int WIDTH { 800 }, HEIGHT { 600 }, CELL_SIZE { 10 };

    Color BACKGROUND { 10, 10, 10, 255 };

    InitWindow(WIDTH, HEIGHT, "Cellular Automaton");
    SetTargetFPS(10);

    Simulation::Data data = Simulation::Create(WIDTH, HEIGHT, CELL_SIZE);

    while (!WindowShouldClose())
    {
        Simulation::Update(data);

        BeginDrawing();
        ClearBackground(BACKGROUND);
        Simulation::Draw(data);
        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}
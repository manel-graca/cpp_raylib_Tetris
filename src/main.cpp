#include "game.hpp"
#include <raylib.h>

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    Color DARK_BLUE = {44, 44, 127, 255};
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    const int CELL_SIZE = 25;
    int FPS = 16;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
    SetTargetFPS(FPS);

    Game game = Game();

    while (!WindowShouldClose())
    {
        game.Update();

        if (eventTriggered(0.05))
            game.MoveBlockDown();

        ClearBackground(DARK_BLUE);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}

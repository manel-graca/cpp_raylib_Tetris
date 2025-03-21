#include "game.hpp"
#include <cstdio>
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
    Image icon = LoadImage("assets/graphics/iconpng24.png");

    Color DARK_BLUE = {44, 44, 127, 255};
    Color LIGHT_BLUE = {59, 85, 162, 255};

    InitWindow(500, 620, "Tetris by Manel");
    SetTargetFPS(60);
    SetWindowIcon(icon);

    Font font = LoadFontEx("assets/fonts/tetris-the-absolute-the-grand-master-2.ttf", 32, 0, 0);

    Game game = Game();

    while (!WindowShouldClose())
    {
        game.Update();

        if (eventTriggered(0.2))
            game.MoveBlockDown();

        BeginDrawing();
        ClearBackground(DARK_BLUE);
        DrawTextEx(font, "Score", {355, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {355, 175}, 38, 2, WHITE);

        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 28, 2, WHITE);
        }

        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, LIGHT_BLUE);

        char scoreText[10];
        sprintf_s(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, LIGHT_BLUE);
        game.Draw();
        EndDrawing();
    }
    UnloadImage(icon);
    UnloadFont(font);
    CloseWindow();
}

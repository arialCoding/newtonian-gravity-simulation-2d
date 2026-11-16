#include "raylib.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Color background = (Color){ 0x12, 0x12, 0x12, 255 };

    InitWindow(screenWidth, screenHeight, "GRAVITY SIMULATION - V1: Newtonian, 2D");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(background);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

#include "raylib.h"

#include "GRV/world.h"

const double zoomFactor = 50; // 1 meter = zoomFactor pixels

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Color background = (Color){0x12, 0x12, 0x12, 255};

    grv_world* world = grv_initWorld();
    grv_addObject(world, 10, 0.5, 5, 12, (grv_color){255, 0, 0, 255});
    grv_addObject(world, 10, 0.8, 13, 12, (grv_color){0, 128, 255, 255});
    grv_addObject(world, 100, 2, 9, 3, (grv_color){0, 180, 100, 255});

    InitWindow(screenWidth, screenHeight, "GRAVITY SIMULATION - V1: Newtonian, 2D");

    double start = GetTime();
    double dt = 0.016;

    while(!WindowShouldClose())
    {
        update(world, dt);

        BeginDrawing();

        ClearBackground(background);

        render(world, zoomFactor);

        EndDrawing();

        dt = GetTime() - start;
        start = GetTime();
    }

    CloseWindow();

    grv_destroyWorld(world);

    return 0;
}

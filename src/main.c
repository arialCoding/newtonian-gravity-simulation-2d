#include "raylib.h"

#include "GRV/force.h"
#include "GRV/object.h"

typedef struct grv_color_t
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} grv_color;

struct grv_object_t
{
    unsigned int id;
    double mass;   // kg
    double radius; // m
    grv_vector2d position;
    grv_vector2d velocity; // ||velocity|| -> m/s
    grv_vector2d cumulated_acceleraton;
    grv_color color;
};

const int zoomFactor = 50;

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Color background = (Color){0x12, 0x12, 0x12, 255};

    grv_object* obj1 = grv_createObject(2, 1, 300, 300, grv_makeColor(255, 0, 0, 255));

    grv_addForce(obj1, (grv_vector2d){0, 50});

    InitWindow(screenWidth, screenHeight, "GRAVITY SIMULATION - V1: Newtonian, 2D");

    double start = GetTime();
    double dt = 0.016;

    while(!WindowShouldClose())
    {
        grv_updatePosition(obj1, dt);

        BeginDrawing();

        ClearBackground(background);

        DrawCircle(obj1->position.x, obj1->position.y, obj1->radius * zoomFactor, *(Color*)(&obj1->color));

        EndDrawing();

        dt = GetTime() - start;
        start = GetTime();
    }

    CloseWindow();

    grv_destroyObject(obj1);

    return 0;
}

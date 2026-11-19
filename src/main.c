#include "raylib.h"
#include "GRV/world.h"
#include <math.h>

const double zoomFactor = 0.5e-5; // 1 meter = zoomFactor pixels
const double G = 1e10;          // Tweaked gravitational constant for fast testing

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    Color background = (Color){0x12, 0x12, 0x12, 255};

    // Sun centered horizontally, above Earth
    const double sunX = (screenWidth * 0.5) / zoomFactor;
    const double sunY = (screenHeight * 0.45) / zoomFactor;
    const double sunMass = 5e13;
    const double sunRadius = 1.4e7; 

    // Earth below the Sun
    const double earthX = (screenWidth * 0.5) / zoomFactor;
    const double earthY = (screenHeight * 0.90) / zoomFactor;
    const double earthMass = 8e11;
    const double earthRadius = 6.371e6;

    // Moon orbiting Earth (placed slightly above Earth so it stays well inside the window)
    const double moonX = earthX;
    const double moonY = earthY - earthRadius * 1.5;
    const double moonMass = 1e9;
    const double moonRadius = 1.737e6;

    // Earth's circular orbit speed around the Sun (2D distance, moving right: +vx)
    const double sunEarthDist = hypot(earthX - sunX, earthY - sunY);
    const double earthOrbitSpeed = sqrt((G * sunMass) / sunEarthDist);
    const double earthVx = earthOrbitSpeed;
    const double earthVy = 0.0;

    // Moon's circular orbit speed around Earth + Earth's own velocity
    const double earthMoonDist = hypot(moonX - earthX, moonY - earthY);
    const double moonRelativeSpeed = sqrt((G * earthMass) / earthMoonDist);
    const double moonVx = earthVx + moonRelativeSpeed;
    const double moonVy = earthVy;

    grv_world* world = grv_initWorld();
    grv_addObject(world, sunMass, sunRadius, sunX, sunY, 0.0, 0.0, (grv_color){255, 200, 30, 255});
    grv_addObject(world, earthMass, earthRadius, earthX, earthY, earthVx, earthVy, (grv_color){0, 180, 100, 255});
    grv_addObject(world, moonMass, moonRadius, moonX, moonY, moonVx, moonVy, (grv_color){255, 60, 60, 255});

    InitWindow(screenWidth, screenHeight, "GRAVITY SIMULATION - V1: Newtonian, 2D");

    double start = GetTime();
    double dt = 0.016;

    while (!WindowShouldClose())
    {
        update(world, dt);

        BeginDrawing();
        ClearBackground(background);
        render(world, zoomFactor);
        EndDrawing();

        dt = GetTime() - start;
        if (dt > 0.05) dt = 0.05;
        start = GetTime();
    }

    CloseWindow();
    grv_destroyWorld(world);

    return 0;
}
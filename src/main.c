#include "GRV/world.h"
#include "core/color.h"
#include "raylib.h"
#include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

double zoomFactor = 5e-6; // 1 meter = zoomFactor pixels
double cameraX = SCREEN_WIDTH / 2.0;
double cameraY = SCREEN_HEIGHT / 2.0;

const double G = 1e10; // Tweaked gravitational constant for fast testing

void handleEvents(double dt);

int main()
{
    const int screenWidth = SCREEN_WIDTH;
    const int screenHeight = SCREEN_HEIGHT;
    Color background = (Color){0x12, 0x12, 0x12, 255};

    Camera2D camera = {0};
    camera.target = (Vector2){0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Sun centered
    const double sunX = (screenWidth * 0.5) / zoomFactor;
    const double sunY = (screenHeight * 0.5) / zoomFactor;
    const double sunMass = 5e13;
    const double sunRadius = 1.4e7;

    // Earth to the right of the Sun
    const double earthX = (screenWidth * 0.9) / zoomFactor;
    const double earthY = (screenHeight * 0.50) / zoomFactor;
    const double earthMass = 8e11;
    const double earthRadius = 6.371e6;

    // Moon orbiting Earth (placed slightly above Earth so it stays well inside the window)
    const double moonX = earthX;
    const double moonY = earthY - earthRadius * 1.5;
    const double moonMass = 1e9;
    const double moonRadius = 1.737e6;

    // Earth's circular orbit speed around the Sun (2D distance, moving up: -vy)
    const double sunEarthDist = hypot(earthX - sunX, earthY - sunY);
    const double earthOrbitSpeed = sqrt((G * sunMass) / sunEarthDist);
    const double earthVx = 0.0;
    const double earthVy = -earthOrbitSpeed;

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

    while(!WindowShouldClose())
    {
        handleEvents(dt);

        camera.offset.x = (float)(cameraX - screenWidth / 2.0);
        camera.offset.y = (float)(cameraY - screenHeight / 2.0);

        update(world, dt);

        BeginDrawing();
        ClearBackground(background);

        BeginMode2D(camera);
        render(world, zoomFactor);
        EndMode2D();

        EndDrawing();

        dt = GetTime() - start;
        if(dt > 0.05) dt = 0.05;
        start = GetTime();
    }

    CloseWindow();
    grv_destroyWorld(world);

    return 0;
}

void handleEvents(double dt)
{
    if(IsKeyPressed(KEY_P)) zoomFactor += 0.2e-6;
    if(IsKeyPressed(KEY_M) && zoomFactor > 0.4e-6) zoomFactor -= 0.2e-6;

    if(IsKeyDown(KEY_W)) cameraY += 100 * dt;
    if(IsKeyDown(KEY_S)) cameraY -= 100 * dt;
    if(IsKeyDown(KEY_A)) cameraX += 100 * dt;
    if(IsKeyDown(KEY_D)) cameraX -= 100 * dt;
}
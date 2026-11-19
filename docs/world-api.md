# World API

The world API in `include/GRV/world.h` manages simulation objects and provides update and draw operations. The world owns the objects and forces it creates; destroy it when the simulation is finished.

## Functions

- `grv_initWorld()` creates and returns an empty world.
- `grv_addObject(world, mass, radius, x, y, vx, vy, color)` adds an object with its mass, radius, position, velocity, and RGBA color. Mass, radius, position, and velocity use the simulation's consistent units (the demo uses kg, meters, and meters per second). The implementation supports up to 256 objects; additional additions are ignored.
- `update(world, dt)` advances the simulation by `dt` seconds. It recalculates pairwise gravity, applies accelerations, and updates velocities and positions. The gravitational constant is currently fixed in `src/core/calculations.c`.
- `render(world, zoom)` draws the world's objects through raylib, scaling their positions and radii by `zoom`. Call it between raylib's `BeginDrawing`/`EndDrawing`; use `BeginMode2D`/`EndMode2D` around it when applying a camera.
- `grv_destroyWorld(world)` frees the world and all objects and forces it owns.

The `grv_color` type passed to `grv_addObject` is declared in `src/core/color.h`. A minimal use follows:

```c
grv_world* world = grv_initWorld();
grv_addObject(world, 1e10, 1e6, 0, 0, 0, 0, (grv_color){255, 200, 30, 255});

update(world, 0.016);
render(world, zoom);

grv_destroyWorld(world);
```

Each added object interacts gravitationally with every other object, so the number of pairwise forces grows quadratically with object count.

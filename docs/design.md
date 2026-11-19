# Design

## Architecture

- `src/main.c` creates the initial Sun–Earth–Moon scene and owns the raylib window, input, camera, and frame loop.
- The core library in `src/core/` separates world management, object state, force application, vector operations, and gravity calculations. Its public world interface is declared in `include/GRV/world.h`.
- Each frame, the world clears accumulated accelerations, recalculates and applies pairwise gravitational forces, then updates object positions and velocities. Rendering walks the world objects and draws them through raylib.

## Design decisions

- Physics state uses double-precision values in simulation units; the render path scales positions and radii by `zoomFactor` to convert them to screen coordinates. The raylib `Camera2D` provides view movement independently.
- Gravitational interactions are represented as forces between object pairs, keeping force calculation and application separate from world updates.
- The frame loop uses elapsed time capped at 0.05 seconds to limit large simulation steps after a slow frame.
- The initial three-body setup is defined in `main.c` to keep the demo straightforward to configure. The world supports adding objects through its public API.

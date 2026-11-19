#pragma once

typedef struct grv_color_t grv_color;
typedef struct grv_world_t grv_world;

grv_world* grv_initWorld();

void grv_destroyWorld(grv_world* self);

void grv_addObject(grv_world* self, double mass, double radius, double x, double y, double vx, double vy, grv_color color);

void update(grv_world* self, double dt);

void render(grv_world* self, double zoom);
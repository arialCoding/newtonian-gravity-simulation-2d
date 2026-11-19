#include "GRV/world.h"
#include "calculations.h"
#include "force.h"
#include "object.h"

#include <stdlib.h>

#define MAX_OBJ_COUNT 256
#define MAX_FORCE_COUNT (MAX_OBJ_COUNT * (MAX_OBJ_COUNT - 1))

grv_object* OBJECTS_ARENA[MAX_OBJ_COUNT];
grv_force* FORCES_ARENA[MAX_FORCE_COUNT];

void recalcGravityForce(grv_force* force);

struct grv_world_t
{
    grv_object** objects;
    grv_force** forces;

    unsigned int object_count;
    unsigned int force_count;
};

grv_world* grv_initWorld()
{
    grv_world* world = malloc(sizeof(grv_world));

    world->objects = OBJECTS_ARENA;
    world->object_count = 0;

    world->forces = FORCES_ARENA;
    world->force_count = 0;

    return world;
}

void grv_destroyWorld(grv_world* self)
{
    for(int i = 0; i < self->force_count; i++)
        grv_destroyForce(self->forces[i]);
    for(int i = 0; i < self->object_count; i++)
        grv_destroyObject(self->objects[i]);

    free(self);
}

void grv_addObject(grv_world* self, double mass, double radius, double x, double y, double vx, double vy, grv_color color)
{
    if(self->object_count >= MAX_OBJ_COUNT || self->force_count >= MAX_FORCE_COUNT) return;

    grv_object* object = grv_createObject(mass, radius, x, y, color);

    grv_setVelocity(object, vx, vy);

    self->objects[self->object_count] = object;

    if(!self->object_count++) return;

    for(int i = 0; i < self->object_count - 1; i++)
    {
        self->forces[self->force_count] = grv_createForce((grv_vector2d){0, 0}, object, self->objects[i]);
        recalcGravityForce(self->forces[self->force_count++]);
    }
}

void update(grv_world* self, double dt)
{
    for(int i = 0; i < self->object_count; i++)
        grv_resetAcceleration(self->objects[i]);

    for(int i = 0; i < self->force_count; i++)
    {
        grv_force* force = self->forces[i];
        recalcGravityForce(force);
        grv_applyForce(force);
    }

    for(int i = 0; i < self->object_count; i++)
        grv_updatePosition(self->objects[i], dt);
}

void render(grv_world* self, double zoom)
{
    for(int i = 0; i < self->object_count; i++)
        grv_drawObject(self->objects[i], zoom);
}

void recalcGravityForce(grv_force* force)
{
    const grv_object* object;
    const grv_object* other;

    grv_getActors(force, &object, &other);

    grv_vector2d self_pos = grv_getPosition(object);
    grv_vector2d other_pos = grv_getPosition(other);

    grv_vector2d force_vector = (grv_vector2d){0, 0};

    grv_vector_add(&force_vector, &self_pos);
    grv_vector_sub(&force_vector, &other_pos);
    grv_vector_normalize(&force_vector);

    double force_value = grv_gravityForce(grv_getMass(object), grv_getMass(other),
                                          grv_distanceSquare(self_pos.x, self_pos.y, other_pos.x, other_pos.y));

    grv_vector_scale(&force_vector, force_value);

    grv_updateForceVector(force, force_vector.x, force_vector.y);
}
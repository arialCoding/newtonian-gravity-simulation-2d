#include "GRV/object.h"
#include "GRV/vector.h"

#include <stdlib.h>
#include <raylib.h>

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

static unsigned int current_id = 0;

grv_object* grv_createObject(double mass, double radius, double x, double y, grv_color color)
{
    grv_object* obj = malloc(sizeof(grv_object));

    obj->id = current_id++;
    obj->mass = mass;
    obj->radius = radius;
    obj->position = (grv_vector2d){x, y};
    obj->velocity = (grv_vector2d){0, 0};
    obj->cumulated_acceleraton = (grv_vector2d){0, 0};
    obj->color = color;

    return obj;
}

void grv_destroyObject(grv_object* object)
{
    free(object);
}

void grv_addForce(grv_object* object, grv_vector2d force_vector)
{
    if(!object)
        return;

    grv_vector_scale(&force_vector, 1 / (object->mass));           // convert to acceleration
    grv_vector_add(&object->cumulated_acceleraton, &force_vector); // add to cumulated acceleration
}

void grv_updatePosition(grv_object* self, double dt)
{
    grv_vector2d dp = grv_vector_scaled(&self->velocity, dt);
    grv_vector2d dv = grv_vector_scaled(&self->cumulated_acceleraton, dt);

    grv_vector_add(&self->position, &dp);
    grv_vector_add(&self->velocity, &dv);
}

void grv_resetAcceleration(grv_object* self)
{
    self->cumulated_acceleraton.x = 0;
    self->cumulated_acceleraton.y = 0;
}

void grv_drawObject(grv_object* self, double zoom)
{
    DrawCircle(self->position.x*zoom, self->position.y*zoom, self->radius * zoom, *(Color*)&self->color);
}

double grv_getMass(const grv_object* self)
{
    return self->mass;
}

double grv_getRadius(const grv_object* self)
{
    return self->radius;
}

grv_vector2d grv_getPosition(const grv_object* self)
{
    return self->position;
}


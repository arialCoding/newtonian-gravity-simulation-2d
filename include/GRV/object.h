#pragma once

#include "color.h"
#include "vector.h"

typedef struct grv_object_t grv_object;

grv_object* grv_createObject(double mass, double radius, double x, double y, grv_color color);

void grv_destroyObject(grv_object* object);

void grv_addForce(grv_object* object, grv_vector2d force_vector);

void grv_updatePosition(grv_object* self, double dt);

void grv_setVelocity(grv_object* self, double vx, double vy);

void grv_resetAcceleration(grv_object* self);

void grv_drawObject(grv_object* self, double zoom);

double grv_getMass(const grv_object* self);

double grv_getRadius(const grv_object* self);

grv_vector2d grv_getPosition(const grv_object* self);


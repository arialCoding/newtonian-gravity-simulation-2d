#pragma once
#include "vector.h"

typedef struct grv_object_t grv_object;
typedef struct grv_color_t grv_color;

grv_object* grv_createObject(double mass, double radius, double x, double y, grv_color color);

void grv_destroyObject(grv_object* object);

void grv_addForce(grv_object* object, grv_vector2d force_vector);

void grv_updatePosition(grv_object* self, double dt);

grv_color grv_makeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

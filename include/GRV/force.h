#pragma once

#include "object.h"

typedef struct grv_force_t grv_force;

grv_force* grv_createForce(grv_vector2d force_vector, grv_object* actor, grv_object* reciever);

void grv_destroyForce(grv_force* self);

void grv_applyForce(grv_force* force);

void grv_getForceVector(grv_force* force, double* x, double* y);

void grv_getActors(grv_force* self, const grv_object** actor, const grv_object** reciever);

void grv_updateForceVector(grv_force* force, double x, double y);
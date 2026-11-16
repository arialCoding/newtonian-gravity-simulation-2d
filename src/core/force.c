#include "GRV/force.h"

struct grv_force_t
{
    grv_vector2d force_vector;
    grv_object* actor;
    grv_object* reciever;
};

grv_force grv_createForce(grv_vector2d force_vector, grv_object* actor, grv_object* reciever)
{
    grv_force force;
    force.force_vector = force_vector;
    force.actor = actor;
    force.reciever = reciever;

    return force;
}

void grv_applyForce(grv_force* force)
{
    if(!force) return;

    grv_addForce(force->reciever, force->force_vector);

    if(force->actor) grv_addForce(force->actor, grv_vector_scaled(&force->force_vector, -1));
}

void grv_getForceVector(grv_force* force, double* x, double* y)
{
    if(x) *x = force->force_vector.x;
    if(y) *y = force->force_vector.y;
}
#include "vector.h"
#include "math.h"

void grv_vector_add(grv_vector2d* self, const grv_vector2d* other)
{
    if(!self || !other) return;

    self->x += other->x;
    self->y += other->y;
}

void grv_vector_sub(grv_vector2d* self, const grv_vector2d* other)
{
    if(!self || !other) return;

    self->x -= other->x;
    self->y -= other->y;
}

void grv_vector_scale(grv_vector2d* self, double scalar)
{
    self->x *= scalar;
    self->y *= scalar;
}

grv_vector2d grv_vector_scaled(grv_vector2d* self, double scalar)
{
    grv_vector2d res;

    res.x = self->x * scalar;
    res.y = self->y * scalar;

    return res;
}

double grv_vector_norm(grv_vector2d* self)
{
    if(!self) return 0;

    return sqrt(self->x * self->x + self->y * self->y);
}

void grv_vector_normalize(grv_vector2d* self)
{
    if(!self) return;

    double norm = grv_vector_norm(self);
    grv_vector_scale(self, 1 / norm);
}

grv_vector2d grv_vector_normalized(grv_vector2d* self)
{
    grv_vector2d res = *self;

    grv_vector_normalize(&res);

    return res;
}
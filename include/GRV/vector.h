#pragma once


typedef struct grv_vector2d_t
{
    double x;
    double y;
} grv_vector2d;


void grv_vector_add(grv_vector2d* self, const grv_vector2d* other);

void grv_vector_scale(grv_vector2d* self, double scalar);

grv_vector2d grv_vector_scaled(grv_vector2d* self, double scalar);

double grv_vector_norm(grv_vector2d* self);

void grv_vector_normalize(grv_vector2d* self);

grv_vector2d grv_vector_normalized(grv_vector2d* self);
#include "GRV/calculations.h"

#define G 1e10


double grv_gravityForce(double m1, double m2, double distance_square)
{
    return (G*m1*m2)/distance_square;
}

double grv_distanceSquare(double x1, double y1, double x2, double y2)
{
    return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}
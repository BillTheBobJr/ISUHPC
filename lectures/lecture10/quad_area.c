#include <math.h>
#include "quadralateral.h"

double quad_area(struct quadralateral* quad) {
    double diagonal1Length = sqrt(pow(quad->p1[0]-quad->p3[0], 2) + pow(quad->p1[1]-quad->p3[1], 2));
    double diagonal2Length = sqrt(pow(quad->p2[0]-quad->p4[0], 2) + pow(quad->p2[1]-quad->p4[1], 2));
    double dotproduct = ((quad->p1[0]-quad->p3[0]) * (quad->p2[0]-quad->p4[0])) + ((quad->p1[1]-quad->p3[1]) * (quad->p2[1]-quad->p4[1]));
    double angle = acos(dotproduct/(diagonal1Length * diagonal2Length));
    return .5 * diagonal1Length * diagonal2Length * sin(angle);
}
#include <math.h>
#include "quadralateral.h"

double quad_perimeter(struct quadralateral* quad) {
    double edge1Length = sqrt(pow(quad->p1[0]-quad->p2[0], 2) + pow(quad->p1[1]-quad->p2[1], 2));
    double edge2Length = sqrt(pow(quad->p2[0]-quad->p3[0], 2) + pow(quad->p2[1]-quad->p3[1], 2));
    double edge3Length = sqrt(pow(quad->p3[0]-quad->p4[0], 2) + pow(quad->p3[1]-quad->p4[1], 2));
    double edge4Length = sqrt(pow(quad->p4[0]-quad->p1[0], 2) + pow(quad->p4[1]-quad->p1[1], 2));
    return edge1Length + edge2Length + edge3Length + edge4Length;
}
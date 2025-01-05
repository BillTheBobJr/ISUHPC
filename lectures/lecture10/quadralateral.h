#ifndef QUADRALATERAL_H
#define QUADRALATERAL_H

//Points are rotating counter-clockwise around the quadralateral
typedef struct quadralateral quadralateral;

struct quadralateral { 
    double p1[2]; //(x, y) coordinates of point 1
    double p2[2]; //(x, y) coordinates of point 2
    double p3[2]; //(x, y) coordinates of point 3
    double p4[2]; //(x, y) coordinates of point 4
};

#endif

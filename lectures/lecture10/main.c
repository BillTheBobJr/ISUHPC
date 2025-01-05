#include <stdio.h>
#include "quadralateral.h"

int main() {
    double quad_area(struct quadralateral* quad);
    double quad_perimeter(struct quadralateral* quad);

    struct quadralateral quad = {{0,0}, {5, 2}, {4,3}, {1,2}};

    double area = quad_area(&quad);
    double perimeter = quad_perimeter(&quad);

    printf("Area = %f\nPerimeter = %f\n", area, perimeter);


    return 0;
}
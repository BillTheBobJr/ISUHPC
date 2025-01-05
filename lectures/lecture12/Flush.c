#include <stdio.h>
#include <stdlib.h>

#include "node.h"

// Allows us to read inputs again
void Flush()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

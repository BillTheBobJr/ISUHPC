#include <stdio.h>
#include <stdlib.h>
#include "node.h"

// Preforms the operation specified in the operation parameter
// On the top two elements in the stack, then places the new
// Calculated value on top of the stack
void PreformOperation(node** top, const char operation) {
    int num1;
    int num2;
    int temp;
    Pop(top, &num1);
    Pop(top, &num2);
    switch(operation) {
        case '*':
            temp = num2 * num1;
            break;
        case '/':
            temp = num2 / num1;
            break;
        case '+':
            temp = num2 + num1;
            break;
        case '-':
            temp = num2 - num1;
            break;                        
        default:
            printf("Invalid Operator %c", (char)operation);
            exit(0);
    }
    Push(top, temp);
}
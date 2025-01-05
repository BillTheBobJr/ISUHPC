#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "node.h"


// This program takes in an equation of non-negative integers and output
// The solution value of the equation using integer math
int main() {

    int len;

    // This stack holds the numbers in the equation
    node* numHead = NULL;
    // This stack holds the operations preformed in the equation
    // The operations are stored as integers
    node* opHead = NULL;

    printf("Please enter length of equation (number of characters):");
    scanf("%d", &len);

    Flush();

    char equation[len + 1];

    printf("Please enter equation:");
    fgets(equation, len + 1, stdin);

    int isNum = 0;
    int currVal = 0;

    // Iterates over character in the equation
    for(int i = 0; i < len; i++) {

        //Reads the numbers from the input equation
        //And transforms them from char data type to int data type
        if(isdigit(equation[i])) {
            char currChar = equation[i];
            isNum = 1;
            currVal = currVal * 10 + atoi(&currChar);
            // If this is the last character we read in,
            // Then we save the inprogress number
            if(i == len - 1) Push(&numHead, currVal);
            continue;
        } 

        //Once a number is fully read, we add it to the number stack
        if(isNum) {
            Push(&numHead, currVal);
            isNum = 0;
            currVal = 0;
        }

        // If we are processing an operation that isn't the end of a parentheses
        if(equation[i] != ')') {
            int size;
            GetStackSize(opHead, &size);

            // We check to see if we already have stored a symbol
            // If we have, then we preform the stored operations, only if they follow PEMDAS
            // (Parenthese, exponetial, multiplication, division, addition, subtraction)
            // Otherwise, we just store the operation
            while(size != 0) {
                // Specifically, if we are processing the start of a parentheses,
                // Then we just store it, as the value it represents once it is computed
                // Is currently unknown
                if(equation[i] == '(') break;
                int press = 1;
                if(equation[i] == '+' || equation[i] == '-') press = 0;
                int op;
                Peek(&opHead, &op);

                // Here we determine if preforming the operation on the top 
                // of the operation stack follows PEMDAS 
                if(!((op == (int)'+' || op == (int)'-') && press == 1) && op != (int)'(') {
                    // If it follows PEMDAS, we preform the operation
                    Pop(&opHead, &op);
                    PreformOperation(&numHead, (char)op);
                } else {
                    break;
                }

                GetStackSize(opHead, &size);
            }

            // We then add the symbol we are processing to the operation stack
            Push(&opHead, (int) equation[i]);
        } else {

            // If we are processing the end of a parentheses, then 
            // We need to process ever operation on the top of the
            // Operation stack until we reach the start of the parentheses
            int curr;
            Pop(&opHead, &curr);
            while(curr != (int)'(') {
                PreformOperation(&numHead, (char)curr);
                Pop(&opHead, &curr);
            }
        }
    }

    // Once we are done processing all characters in the equation
    // We must go preform ever operation left in the operation stack
    // Once we have done that, we know we will only have one number in
    // the number stack, which will be the solution to the equation
    int size;
    GetStackSize(opHead, &size);
    for(int i = 0; i < size; i++) {
        int curr;
        Pop(&opHead, &curr);
        PreformOperation(&numHead, (char)curr);
        GetStackSize(opHead, &size);
    }


    // We finally retrieve the answer to the equation and print it
    int result;
    Pop(&numHead, &result);

    printf("The answer to this equation using only integer math is %d\n", result);

    return 0;
}
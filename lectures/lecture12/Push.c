#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void Push(node** top, const int input) {
    if(*top == NULL) {
        *top =(node*) malloc(sizeof(struct node));
        (*top)->next = NULL;
        (*top)->value = input;
        (*top)->position = 1;
    } else {
        node* temp;
        temp =( node *) malloc ( sizeof ( struct node));
        temp ->next = *top;
        temp -> value = input ;
        temp -> position = 1;
        *top = temp;
        node* ptr = (* top)->next;
        while (ptr != NULL) {
            ptr -> position = ptr -> position +1;
            ptr = ptr ->next;
        }
    }
}
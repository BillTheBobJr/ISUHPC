#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("** Monty Hall Simulator **\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

    int winningPosition = rand() % 3 + 1;
    int selection = -1;
    int winner = 0;
    char switchDoors = 'a';

    printf("Pick a Door:\n");
    scanf("%d", &selection);

    int remove = 0;

    if(selection == winningPosition) {
        remove = ((rand() % 2) + winningPosition + 1) % 3;
    } else {
        remove = 6 - winningPosition - selection;
    }

    printf("Door %d has been removed, would you like to switch doors? (y/n)\n", remove);
    scanf("\n%c", &switchDoors);

    winner = (switchDoors == 'y') ^ (selection == winningPosition);

    if(winner) {
        printf("You Win!!!\n");
    } else {
        printf("You Lose!!\n");
    }

    return 0;
}
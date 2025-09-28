#include <stdio.h>
#include <stdlib.h>
# include "headers.h"

int** board = createGrid();
int row;
int column;

printf("Welcome to Connect Four!");

char playerA = 'A';
char playerB = 'B';
printf("Player A: %c\n", playerA);
printf("Player B: %c\n\n", playerB);

print(board);

printf("Player %c, choose a column (0-7): ", playerA);
 scanf("%d", &column);



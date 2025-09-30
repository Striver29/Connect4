#include <stdio.h>
#include <stdlib.h>
# include "headers.h"

int row;
int column;

void main(){
    
int** board = createGrid();
printf("Welcome to Connect Four!");

char playerA = 'A';
char playerB = 'B';
char currentPlayer= playerA;
printf("Player A: %c\n", playerA);
printf("Player B: %c\n\n", playerB);

print(board);

while (true){
printf("Player %c, choose a column (0-7): ", playerA);
 scanf("%d", &column);

 print(board);

 if (currentPlayer == playerA) {
            currentPlayer = playerB;
        } else {
            currentPlayer = playerA;
        }
}
printf("Player %c wins!", currentPlayer);
printf("Program finished with exit code 0");
}


//// Place a checker for the player in the chosen column
// Returns 1 if successful, 0 if column is full
int placeChecker(char board[ROWS][COLS], int col, char player) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][col] == '-') {
            board[i][col] = player;
            return 1;

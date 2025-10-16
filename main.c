#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int row;
int column;

int main(int argc, char** argv){
    
int** board = createGrid();
printf("Welcome to Connect Four!\n");

printf("Do you want to play against human or bot? \nEnter 0 for human or 1 for bot: ");
int x;
fflush(stdout); 
scanf("%d",&x);

int mode = 0; 
if(x==1){
printf("Choose the level: \nEnter 1 for easy, 2 for Medium, 3 for Hard:  ");
fflush(stdout); 
scanf("%d",&mode);
}

char playerA = 'A';
char playerB = 'B';
char currentPlayer= playerA;
printf("\nPlayer A: %c\n", playerA);
printf("Player B: %c\n\n", playerB);

while (1){ 
// print empty  broad first
print(board);


printf("Player %c, choose a column (1-7): ", currentPlayer);
fflush(stdout);

if(currentPlayer == playerA) {
    scanf("%d", &column); 
}

if(currentPlayer == playerB) {
    if(mode == 1) {
        column = easyBot(board); 
    } else {
        scanf("%d", &column);
    }
}

if (column < 1 || column >7){
    printf("\nInvalid! choose another.\n");
         continue;
}



if (!place(board, column, currentPlayer)) {
      printf("\nColumn full! Choose another.\n");
         continue; 
    }

int win = checkWin(board, (64 - currentPlayer) * -1); 

if(win == 1) {
    print(board);
    printf("Player %c wins!", currentPlayer);
    break;
} 


// switch players
 if (currentPlayer == playerA) {
            currentPlayer = playerB;
        } else {
            currentPlayer = playerA;
        }
}


for(int i = 0; i < 7; i++) {
    free(board[i]); 
}

free(board);
}

#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include "unistd.h"

int row;
int column;

int main(int argc, char** argv){
    
    
int** board = createGrid();
printf("Welcome to Connect Four!\n");

char playerA = 'A';
char playerB = 'B';
char currentPlayer= playerA;
printf("Player A: %c\n", playerA);
printf("Player B: %c\n\n", playerB);

while (1){ 
// print empty  broad first
print(board);


printf("Player %c, choose a column (1-7): ", currentPlayer);
sleep(1); //to Print above before taking value
 scanf("%d", &column);

 if(column == 10) {
    break; 
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

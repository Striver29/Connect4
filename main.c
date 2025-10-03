#include <stdio.h>
#include <stdlib.h>
# include "headers.h"

int row;
int column;

int main(int argc, char** argv){
    
    
int** board = createGrid();
printf("Welcome to Connect Four!");

char playerA = 'A';
char playerB = 'B';
char currentPlayer= playerA;
printf("Player A: %c\n", playerA);
printf("Player B: %c\n\n", playerB);

while (1){ 
// print empty  broad first
print(board);


printf("Player %c, choose a column (1-7): ", playerA);
 scanf("%d", &column);

// eza msh value akbar mn column 
if (column < 1 || column >7){
    printf("Invalid! choose another.\n");
         continue;
}


// eza fe place 
if (!place(board, column, currentPlayer)) {
      printf("Column full! Choose another.\n");
         continue; 
    }


// switch players
 if (currentPlayer == playerA) {
            currentPlayer = playerB;
        } else {
            currentPlayer = playerA;
        }
}
printf("Player %c wins!", currentPlayer);
printf("Program finished with exit code 0");

for(int i = 0; i < 7; i++) {
    free(board[i]); 
}

free(board);
}

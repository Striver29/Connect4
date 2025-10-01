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


for (i=0; i=7; i++){
    for (j=0;j=6;j++){
     
    }
}

while (true){ 
// print empty  broad first
print(board);


printf("Player %c, choose a column (0-7): ", playerA);
 scanf("%d", &column);

// eza msh value akbar mn column 
if (column < 0 || column >=7){
    Printf("Invalid! choose another.\n");
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
}
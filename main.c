#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int row;
int column;

int main(int argc, char** argv){
    
int** board = createGrid();
printf("Welcome to Connect Four!\n");

printf("\nDo you want to play against a human or a bot? \nEnter 0 for human\nEnter 1 for bot\n");
int x;
fflush(stdout); 
scanf("%d",&x);

printf("\n"); 

int mode = 0; 
if(x==1){
printf("Choose the level: \nEnter 1 for easy\nEnter 2 for Medium\nEnter 3 for Hard\n");
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
    int status = scanf("%d", &column); 

    if(status == 0) { //makes sure nothing gets added but legal indices 
        printf("\nInvalid! choose another.\n");
        while(getchar() != '\n'); //cleans buffer
        continue;
    }
}

if(currentPlayer == playerB) {
    if(mode == 1) {
        column = easyBot(board); 
    } else if(mode == 2) {
        column = mediumBot(board); 
        
        else if(mode == 3) 
            column = hardBot(board); 
    } else {
        int status = scanf("%d", &column);

        if(status == 0) {
            printf("\nInvalid! choose another.\n");
            while(getchar() != '\n'); 
            continue;
        }
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

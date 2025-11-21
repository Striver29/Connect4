#include <stdio.h>

// check move
int checkMove(int** arr, int column){
  if(column >7 && column<0){
    return 0;}
  if (arr[0][column]==0){
    return 1;
 }
return 0; 
}

int checkFull(int** arr) {
    for(int i = 0; i < 7; i++) {
        if(arr[0][i] == 0) {
            return 0; 
        }
    }

    return 1; 
}

int LandingRow(int** arr, int col) {
    for(int i = 5; i >= 0; i--) {
        if(arr[i][col] == 0) {
            return i; 
        }
    }

    return -1; 
}

void simulatePlace(int** arr, int row, int col, int player) {
    arr[row][col] = player; 
}

// undoMove
void undoMove(int** arr, int row , int col){
    arr[row][col]=0;
}

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

int evaluateBoard(int** arr) {
    int score = 0; 
    int BotCount = 0; 
    int OppCount = 0; 
    int EmptyCount = 0; 

    for(int i = 0; i < 6; i++) {
        if(arr[i][3] == 2) 
            BotCount++;
        else if(arr[i][3] == 1) 
            OppCount++;
        else if(arr[i][3] == 0) 
            EmptyCount++;
    }

    //give small bonus for center pieces
    score += BotCount * 3;

    //Horizontal swap
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 4; j++) {
            int val[4] = {arr[i][j], arr[i][j+1], arr[i][j+2], arr[i][j+3]};
            score += evaluateWindow(val); 
        }
    } 

    //Vertical swap
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 3; j++) {
            int val[4] = {arr[j][i], arr[j+1][i], arr[j+2][i], arr[j+3][i]};
            score += evaluateWindow(val); 
        }
    }


    //positive-diagonal swap
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            int val[4] = {arr[i][j], arr[i+1][j+1], arr[i+2][j+2], arr[i+3][j+3]};
            score += evaluateWindow(val);
        }
    }

    //negative-diagonal swap
    for(int i = 0; i < 3; i++) {
        for(int j = 6; j > 2; j--) {
            int val[4] = {arr[i][j], arr[i+1][j-1], arr[i+2][j-2], arr[i+3][j-3]};
            score += evaluateWindow(val);
        }
    }

    return score; 
}

int evaluateWindow(int arr[]) {
    int bot = 0; 
    int opp = 0; 
    int empty = 0; 

    for(int i = 0; i < 4; i++) {
        if(arr[i] == 2)
            bot++; 
        else if(arr[i] == 1)
            opp++; 
        else if(arr[i] == 0) 
            empty++; 
    }

    if(bot == 4)
        return 1000000;
    else if(bot == 3 && empty == 1) 
        return 50; 
    else if(bot == 2 && empty == 2) 
        return 10; 
    else if(opp == 3 && empty == 1)
        return -300; 

    return 0; 
}
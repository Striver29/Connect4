#include <stdio.h>
#include "headers.h"
#define BOT 2
#define OPP 1
#define DEPTH 6
#define INFINITY 100000000000


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
void undoPlace(int** arr, int row , int col){
    arr[row][col]=0;
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
        return 100000;
    else if(bot == 3 && empty == 1) 
        return 100; 
    else if(bot == 2 && empty == 2) 
        return 10; 
    else if(opp == 3 && empty == 1)
        return -300; 
    else if(opp == 2 && empty == 2)
        return -10;

    return 0; 
}

int evaluateBoard(int** arr) {
    int score = 0; 
    int BotCount = 0; 

    for(int i = 0; i < 6; i++) {
        if(arr[i][3] == 2) 
            BotCount++;
    }

    //give small bonus for center pieces
    score += BotCount * 6;

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

int minimax(int** arr, int depth, long alpha, long beta, int isMaximising) {
    //base cases
    if(checkWin(arr, BOT)) {
        return 1000000 - depth; 
    } 
    if(checkWin(arr, OPP)) {
        return -1000000 + depth; 
    }
    if(checkFull(arr)){
        return 0; 
    } 
    if(depth == 0) {
        return evaluateBoard(arr);
    }
    
    int move[7] = {3, 2, 4, 1, 5, 0, 6};

    if(isMaximising) {
        long bestScore = -INFINITY; 
        int score = 0;

        for(int i = 0; i < 7; i++) {
            int col = move[i]; 
            int row = LandingRow(arr, col); 
            if(row == -1) 
                continue;
            
            simulatePlace(arr, row, col, BOT); 
            score = minimax(arr, depth-1, alpha, beta, 0);
            undoPlace(arr, row, col); 
            if(score >= bestScore) {
                bestScore = score; 
            }

            if(bestScore >= alpha) 
                alpha = bestScore;  

            if(beta <= alpha)   
                break;
            
        }
        return bestScore; 
    }

    else {
        long bestScore = INFINITY; 

        for(int i = 0; i < 7; i++) {
            int col = move[i]; 
            int row = LandingRow(arr, col); 
            if(row == -1) 
                continue;
            simulatePlace(arr, row, col, OPP); 
            int score = minimax(arr, depth-1, alpha, beta, 1); 
            undoPlace(arr, row, col); 
            if(score <= bestScore)
                bestScore = score; 
            if(bestScore <= beta)
                beta = bestScore; 
            if(beta <= alpha)
                break;
        }

        return bestScore;
    }
}

int hardBot(int** arr) {
    long bestScore = -INFINITY; 
    int bestCol = 3; 
    int full = 0; 

    int move[7] = {3, 2, 4, 1, 5, 0, 6};

    for(int i = 0; i < 7; i++) {
        int col = move[i]; 
        int row = LandingRow(arr, col); 
        if(row == -1) {
            full++; 
            continue;
        }
        simulatePlace(arr, row, col, BOT); 
        int score = minimax(arr, DEPTH-1, -INFINITY, INFINITY, 0); 
        undoPlace(arr, row, col); 

        if(score >= bestScore) {
            bestScore = score; 
            bestCol = col; 
        }
    }

    if(full == 7)
        return -1; 

    bestCol++; 
    return bestCol;
}
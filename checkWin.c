#include <stdio.h>
#include "headers.h"

int checkWin(int** arr, int current) {

    return horizontal(arr, current) || vertical(arr, current) || diagonal(arr, current); 
}



int horizontal(int** arr, int current) {
    int currentLen;
    
    for (int i = 5; i >= 0; i--) {
        currentLen = 0;
        for (int j = 0; j < 7; j++) {
            if (arr[i][j] == current) {
                currentLen++;
                if (currentLen == 4) {
                    return 1;
                }
            } else {
                currentLen = 0;
            }
        }
    }
    return 0;
}

int vertical(int** arr, int current) {
    int currentLen;
    
    for (int i = 0; i < 7; i++) {
        currentLen = 0;
        for (int j = 0; j < 6; j++) {
            if (arr[j][i] == current) {
                currentLen++;
                if (currentLen == 4) {
                    return 1;
                }
            } else {
                currentLen = 0;
            }
        }
    }
    return 0;
}

int diagonal(int** arr, int current) {
    
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 3; j++) {
            if (arr[i][j] == current &&
                arr[i+1][j+1] == current &&
                arr[i+2][j+2] == current &&
                arr[i+3][j+3] == current) {
                return 1;
            }
        }
    }

    
    for (int i = 0; i <= 2; i++) {
        for (int j = 3; j <= 6; j++) {
            if (arr[i][j] == current &&
                arr[i+1][j-1] == current &&
                arr[i+2][j-2] == current &&
                arr[i+3][j-3] == current) {
                return 1;
            }
        }
    }

    return 0;
}

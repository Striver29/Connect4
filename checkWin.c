#include <stdio.h>
#include "headers.h"

int checkWin(int** arr, int current) {

    int currentLen;
    //Check horizontal
    for(int i = 5; i >= 0; i--) {
        currentLen = 0; 
        for(int j = 0; j < 7; j++) {
            if(arr[i][j] == current) {
                currentLen++; 
                if(currentLen == 4) {
                    return 1; 
                }
            } else {
                currentLen = 0; 
            }
        }
    }

    //Check Vertical 
    for(int i = 0; i < 7; i++) {
        currentLen = 0; 
        for(int j = 0; j < 6; j++) {
            if(arr[j][i] == current) {
                currentLen++; 
                if(currentLen == 4) {
                    return 1; 
                }
            } else {
                currentLen = 0; 
            }
        }
    }
    return 0; 
}

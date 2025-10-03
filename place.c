#include <stdio.h>
#include "headers.h"

int place(int** arr, int col, char letter) {
    col--;
    for(int i = 5; i >=0; i--) {
        if(arr[i][col] == 0) {
            if(letter == 'A') {
                arr[i][col] = 1; 
            } else if(letter == 'B') {
                arr[i][col] = 2; 
            }
            
            return 1; 
        }
    }

    return 0; 
}
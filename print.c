#include <stdio.h>
#include "headers.h"

void print(int** arr) {
    
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++) {
            if(arr[i][j] == 0) {
                printf(". ");
            } else if(arr[i][j] == 1) {
                printf("A "); 
            } else if(arr[i][j] == 2) {
                printf("B "); 
            }
        }

        printf("\n");
    }

    for(int i = 1; i < 8; i++) {
        printf("%d ", i); 
    }
}
 
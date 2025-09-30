#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int** createGrid(){
    int n = 7, m = 6;
    int** grid = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        grid[i] = (int*)malloc(m * sizeof(int));
    }

    return grid; 
    
}




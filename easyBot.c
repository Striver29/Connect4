#include <stdio.h> 
#include <stdlib.h>
#include "headers.h"

int easyBot(int** arr) {
    int max = 7; 
    int min = 1; 

    int random = (rand() % (max - min + 1)) + min; 
    return random; 
}

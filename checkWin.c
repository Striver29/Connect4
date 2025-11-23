#include <stdio.h>
#include <pthread.h>
#include "headers.h"

typedef struct CheckArgs {
    int **arr;
    int current;
    int result;
} CheckArgs;


void *horizontal_thread(void *arg) {
    CheckArgs *a = (CheckArgs *)arg;
    a->result = horizontal(a->arr, a->current);
    return NULL;
}

void *vertical_thread(void *arg) {
    CheckArgs *a = (CheckArgs *)arg;
    a->result = vertical(a->arr, a->current);
    return NULL;
}

void *diagonal_thread(void *arg) {
    CheckArgs *a = (CheckArgs *)arg;
    a->result = diagonal(a->arr, a->current);
    return NULL;
}


int checkWin(int** arr, int current) {
    pthread_t th_h, th_v, th_d;

    CheckArgs hArgs = { arr, current, 0 };
    CheckArgs vArgs = { arr, current, 0 };
    CheckArgs dArgs = { arr, current, 0 };

    pthread_create(&th_h, NULL, horizontal_thread, &hArgs);
    pthread_create(&th_v, NULL, vertical_thread, &vArgs);
    pthread_create(&th_d, NULL, diagonal_thread, &dArgs);

    pthread_join(th_h, NULL);
    pthread_join(th_v, NULL);
    pthread_join(th_d, NULL);

    if (hArgs.result || vArgs.result || dArgs.result) {
        return 1;
    }
    return 0;
}

int horizontal(int** arr, int current) {
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

    return 0; 
}

int vertical(int** arr, int current) {
    
    int currentLen; 
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

int diagonal(int** arr, int current) {
    //diagonal (down right) 

    for(int i = 0; i <= 2; i++) {
        for(int j = 0; j <= 3 ; j++) {

            if(arr[i][j] == current && arr[i+1][j+1] == current
            && arr[i+2][j+2] == current && arr[i+3][j+3] == current) {
                return 1; 
            }
        }
    }

    //diagonal (down left) 

    for(int i = 0; i <= 2; i++) {
        for(int j = 3; j <= 6 ; j++) {

            if(arr[i][j] == current && arr[i+1][j-1] == current
            && arr[i+2][j-2] == current && arr[i+3][j-3] == current) {
                return 1; 
            }
        }
    }

    return 0; 
}

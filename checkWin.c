#include <stdio.h>
#include <pthread.h>
#include "headers.h"

typedef struct CheckArgs {
    int **arr;
    int current;
    int result;
} CheckArgs;



static pthread_t th_h, th_v, th_d;
static CheckArgs hArgs, vArgs, dArgs;

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_start = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_done  = PTHREAD_COND_INITIALIZER;

static int work_available = 0;     
static int pending_workers = 0;    
static int initialized = 0;        


int horizontal(int **arr, int current);
int vertical(int **arr, int current);
int diagonal(int **arr, int current);



void *horizontal_thread(void *arg) {
    (void)arg;
    while (1) {
        pthread_mutex_lock(&mtx);
        while (!work_available) {
            pthread_cond_wait(&cond_start, &mtx);
        }
        int **arr = hArgs.arr;
        int current = hArgs.current;
        pthread_mutex_unlock(&mtx);

        int res = horizontal(arr, current);

        pthread_mutex_lock(&mtx);
        hArgs.result = res;
        pending_workers--;
        if (pending_workers == 0) {
            work_available = 0;
            pthread_cond_signal(&cond_done);
        }
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void *vertical_thread(void *arg) {
    (void)arg;
    while (1) {
        pthread_mutex_lock(&mtx);
        while (!work_available) {
            pthread_cond_wait(&cond_start, &mtx);
        }
        int **arr = vArgs.arr;
        int current = vArgs.current;
        pthread_mutex_unlock(&mtx);

        int res = vertical(arr, current);

        pthread_mutex_lock(&mtx);
        vArgs.result = res;
        pending_workers--;
        if (pending_workers == 0) {
            work_available = 0;
            pthread_cond_signal(&cond_done);
        }
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void *diagonal_thread(void *arg) {
    (void)arg;
    while (1) {
        pthread_mutex_lock(&mtx);
        while (!work_available) {
            pthread_cond_wait(&cond_start, &mtx);
        }
        int **arr = dArgs.arr;
        int current = dArgs.current;
        pthread_mutex_unlock(&mtx);

        int res = diagonal(arr, current);

        pthread_mutex_lock(&mtx);
        dArgs.result = res;
        pending_workers--;
        if (pending_workers == 0) {
            work_available = 0;
            pthread_cond_signal(&cond_done);
        }
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}



static void init_checkWin_threads(void) {
    if (initialized) return;
    initialized = 1;

    hArgs.arr = vArgs.arr = dArgs.arr = NULL;
    hArgs.current = vArgs.current = dArgs.current = 0;
    hArgs.result = vArgs.result = dArgs.result = 0;

    pthread_create(&th_h, NULL, horizontal_thread, NULL);
    pthread_create(&th_v, NULL, vertical_thread, NULL);
    pthread_create(&th_d, NULL, diagonal_thread, NULL);
}



int checkWin(int **arr, int current) {
    if (!initialized) {
        init_checkWin_threads();
    }

    pthread_mutex_lock(&mtx);

    
    hArgs.arr = vArgs.arr = dArgs.arr = arr;
    hArgs.current = vArgs.current = dArgs.current = current;
    hArgs.result = vArgs.result = dArgs.result = 0;

    pending_workers = 3;
    work_available = 1;

    
    pthread_cond_broadcast(&cond_start);

    
    while (pending_workers > 0) {
        pthread_cond_wait(&cond_done, &mtx);
    }

    int win = (hArgs.result || vArgs.result || dArgs.result);

    pthread_mutex_unlock(&mtx);

    return win;
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

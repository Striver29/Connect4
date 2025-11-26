#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "headers.h"

#define BOT 2
#define OPP 1
#define DEPTH 10
#define INFINITY 100000000000L

int checkFull(int **arr) {
    for (int i = 0; i < 7; i++) {
        if (arr[0][i] == 0) return 0;
    }
    return 1;
}

int LandingRow(int **arr, int col) {
    for (int i = 5; i >= 0; i--) {
        if (arr[i][col] == 0) return i;
    }
    return -1;
}

void simulatePlace(int **arr, int row, int col, int player) {
    arr[row][col] = player;
}

void undoPlace(int **arr, int row, int col) {
    arr[row][col] = 0;
}

int evaluateWindow(int arr[]) {
    int bot = 0, opp = 0, empty = 0;

    for (int i = 0; i < 4; i++) {
        if (arr[i] == 2) bot++;
        else if (arr[i] == 1) opp++;
        else if (arr[i] == 0) empty++;
    }

    if (bot == 4) return 100000;
    else if (bot == 3 && empty == 1) return 1000;
    else if (bot == 2 && empty == 2) return 50;
    else if (opp == 3 && empty == 1) return -1200;
    else if (opp == 2 && empty == 2) return -50;

    return 0;
}

int evaluateBoard(int **arr) {
    int score = 0, BotCount = 0;

    for (int i = 0; i < 6; i++) {
        if (arr[i][3] == 2) BotCount++;
    }
    score += BotCount * 6;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            int val[4] = { arr[i][j], arr[i][j+1], arr[i][j+2], arr[i][j+3] };
            score += evaluateWindow(val);
        }
    }

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            int val[4] = { arr[j][i], arr[j+1][i], arr[j+2][i], arr[j+3][i] };
            score += evaluateWindow(val);
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            int val[4] = { arr[i][j], arr[i+1][j+1], arr[i+2][j+2], arr[i+3][j+3] };
            score += evaluateWindow(val);
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 6; j > 2; j--) {
            int val[4] = { arr[i][j], arr[i+1][j-1], arr[i+2][j-2], arr[i+3][j-3] };
            score += evaluateWindow(val);
        }
    }

    return score;
}

int minimax(int **arr, int depth, long alpha, long beta, int isMaximising) {
    if (checkWin(arr, BOT)) return 1000000 - depth;
    if (checkWin(arr, OPP)) return -1000000 + depth;
    if (checkFull(arr)) return 0;
    if (depth == 0) return evaluateBoard(arr);

    int move[7] = { 3, 2, 4, 1, 5, 0, 6 };

    if (isMaximising) {
        long bestScore = -INFINITY;

        for (int i = 0; i < 7; i++) {
            int col = move[i], row = LandingRow(arr, col);
            if (row == -1) continue;

            simulatePlace(arr, row, col, BOT);
            int score = minimax(arr, depth - 1, alpha, beta, 0);
            undoPlace(arr, row, col);

            if (score >= bestScore) bestScore = score;
            if (bestScore >= alpha) alpha = bestScore;
            if (beta <= alpha) break;
        }
        return bestScore;
    } else {
        long bestScore = INFINITY;

        for (int i = 0; i < 7; i++) {
            int col = move[i], row = LandingRow(arr, col);
            if (row == -1) continue;

            simulatePlace(arr, row, col, OPP);
            int score = minimax(arr, depth - 1, alpha, beta, 1);
            undoPlace(arr, row, col);

            if (score <= bestScore) bestScore = score;
            if (bestScore <= beta) beta = bestScore;
            if (beta <= alpha) break;
        }
        return bestScore;
    }
}

typedef struct {
    int **board;
    int col;
    int row;
    long score;
} ThreadArgs;

void *threadMinimax(void *arg) {
    ThreadArgs *data = (ThreadArgs *)arg;
    int copyBoard[6][7];

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            copyBoard[i][j] = data->board[i][j];
        }
    }

    int *boardPtr[6];
    for (int i = 0; i < 6; i++) boardPtr[i] = copyBoard[i];

    simulatePlace(boardPtr, data->row, data->col, BOT);
    data->score = minimax(boardPtr, DEPTH - 1, -INFINITY, INFINITY, 0);

    return NULL;
}

int hardBot(int **arr) {
    long bestScore = -INFINITY;
    int bestCol = 3;

    int move[7] = { 3, 2, 4, 1, 5, 0, 6 };

    pthread_t threads[7];
    ThreadArgs args[7];
    int threadCount = 0;

    for (int i = 0; i < 7; i++) {
        int col = move[i], row = LandingRow(arr, col);
        if (row == -1) continue;

        args[threadCount].board = arr;
        args[threadCount].col = col;
        args[threadCount].row = row;
        args[threadCount].score = -INFINITY;

        pthread_create(&threads[threadCount], NULL, threadMinimax, &args[threadCount]);
        threadCount++;
    }

    if (threadCount == 0) return -1;

    for (int i = 0; i < threadCount; i++) pthread_join(threads[i], NULL);

    for (int i = 0; i < threadCount; i++) {
        if (args[i].score >= bestScore) {
            bestScore = args[i].score;
            bestCol = args[i].col;
        }
    }

    return bestCol + 1;
}

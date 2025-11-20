#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

#define ROWS 6
#define COLS 7
#define INF 1000000000

static const int BOT = 2;
static const int OPP = 1;

static int isFull(int **board) {
    for (int j = 0; j < COLS; j++) {
        if (board[0][j] == 0) return 0;
    }
    return 1;
}

static void undoMove(int **board, int col) {
    col--;
    for (int i = 0; i < ROWS; i++) {
        if (board[i][col] != 0) {
            board[i][col] = 0;
            break;
        }
    }
}

static int scoreWindow(int window[4]) {
    int score = 0;
    int botCount = 0;
    int oppCount = 0;
    int emptyCount = 0;

    for (int i = 0; i < 4; i++) {
        if (window[i] == BOT) botCount++;
        else if (window[i] == OPP) oppCount++;
        else emptyCount++;
    }

    if (botCount == 4) score += 100000;
    else if (botCount == 3 && emptyCount == 1) score += 100;
    else if (botCount == 2 && emptyCount == 2) score += 10;

    if (oppCount == 3 && emptyCount == 1) score -= 120;
    else if (oppCount == 2 && emptyCount == 2) score -= 10;

    return score;
}

static int evaluate(int **board) {
    int score = 0;
    int window[4];

    int centerCol = COLS / 2;
    int centerCount = 0;
    for (int i = 0; i < ROWS; i++) {
        if (board[i][centerCol] == BOT) centerCount++;
    }
    score += centerCount * 6;

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j <= COLS - 4; j++) {
            for (int k = 0; k < 4; k++)
                window[k] = board[i][j + k];
            score += scoreWindow(window);
        }

    for (int j = 0; j < COLS; j++)
        for (int i = 0; i <= ROWS - 4; i++) {
            for (int k = 0; k < 4; k++)
                window[k] = board[i + k][j];
            score += scoreWindow(window);
        }

    for (int i = 0; i <= ROWS - 4; i++)
        for (int j = 0; j <= COLS - 4; j++) {
            for (int k = 0; k < 4; k++)
                window[k] = board[i + k][j + k];
            score += scoreWindow(window);
        }

    for (int i = 0; i <= ROWS - 4; i++)
        for (int j = 3; j < COLS; j++) {
            for (int k = 0; k < 4; k++)
                window[k] = board[i + k][j - k];
            score += scoreWindow(window);
        }

    return score;
}

static int minimax(int **board, int depth, int alpha, int beta, int maximizing) {

    if (checkWin(board, BOT)) return 100000 - depth;
    if (checkWin(board, OPP)) return -100000 + depth;
    if (isFull(board) || depth == 0) return evaluate(board);

    int moveOrder[COLS] = {4, 3, 5, 2, 6, 1, 7};

    if (maximizing) {
        int best = -INF;

        for (int mi = 0; mi < COLS; mi++) {
            int col = moveOrder[mi];

            if (board[0][col - 1] != 0) continue;

            place(board, col, 'B');

            int val = minimax(board, depth - 1, alpha, beta, 0);

            undoMove(board, col);

            if (val > best) best = val;
            if (best > alpha) alpha = best;
            if (beta <= alpha) break;
        }

        return best;

    } else {
        int best = INF;

        for (int mi = 0; mi < COLS; mi++) {
            int col = moveOrder[mi];

            if (board[0][col - 1] != 0) continue;

            place(board, col, 'A');

            int val = minimax(board, depth - 1, alpha, beta, 1);

            undoMove(board, col);

            if (val < best) best = val;
            if (best < beta) beta = best;
            if (beta <= alpha) break;
        }

        return best;
    }
}

int hardBot(int **arr) {
    int bestScore = -INF;
    int bestCol = 4;
    int depth = 6;

    int moveOrder[COLS] = {4, 3, 5, 2, 6, 1, 7};

    for (int mi = 0; mi < COLS; mi++) {
        int col = moveOrder[mi];

        if (arr[0][col - 1] != 0) continue;

        place(arr, col, 'B');

        int score = minimax(arr, depth - 1, -INF, INF, 0);

        undoMove(arr, col);

        if (score > bestScore) {
            bestScore = score;
            bestCol = col;
        }
    }

    return bestCol;
}

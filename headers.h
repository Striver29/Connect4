#ifndef HEADERS_H
#define HEADERS_H

void print(int**);
int** createGrid();
int place(int**, int, char);
int checkWin(int** arr, int current); 
int horizontal(int** arr, int current); 
int vertical(int** arr, int current); 
int diagonal(int** arr, int current); 
int easyBot(int** arr); 
#endif

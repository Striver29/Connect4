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
int mediumBot(int** arr); 
int hardBot(int** arr);
int networkServer(char current, int** arr);
int networkClient(char current, int** arr);
#endif

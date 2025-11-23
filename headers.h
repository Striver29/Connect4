#ifndef HEADERS_H
#define HEADERS_H

void print(int**, char);
int** createGrid();
int place(int**, int, char);
int checkWin(int** arr, int current); 
int horizontal(int** arr, int current); 
int vertical(int** arr, int current); 
int diagonal(int** arr, int current); 
int easyBot(int** arr); 
int mediumBot(int** arr); 
int hardBot(int** arr);
int startServer(int port);
int startClient(const char* ip, int port);
void sendMove(int sock, int move);
int receiveMove(int sock);
#endif

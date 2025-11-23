#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int row;
int column;

int main(int argc, char **argv)
{
    int **board = createGrid();
    printf("Welcome to Connect Four!\n");
    printf("\nAre you using Alpine? (Enter y for Yes and n for no): ");
    fflush(stdout); 
    char type; 
    scanf("%c", &type);
    //Networking part
    printf("\nEnable network mode? (Enter s for server, c for client, n for normal): ");
    fflush(stdout); 
    char netMode;
    scanf(" %c", &netMode);

    int network = 0;
    int port = 0;
    int socket_fd = -1;
    char serverIP[64];

    if (netMode == 's' || netMode == 'c')
    {
        network = 1;
        printf("Enter port: ");
        fflush(stdout);
        scanf("%d", &port);

        if (netMode == 'c')
        {
            printf("Enter server IP: ");
            fflush(stdout);
            scanf("%s", serverIP);
        }
    }

    int x = 0;
    int mode = 0;

    char playerA = 'A';
    char playerB = 'B';
    char currentPlayer = playerA;
    int cond = 0;

    
    if (network == 0)
    {
        printf("\nDo you want to play against a human or a bot? \nEnter 0 for human\nEnter 1 for bot\n");
        fflush(stdout);
        scanf("%d", &x);

        printf("\n");

        if (x == 1)
        {
            printf("Choose the level: \nEnter 1 for Easy\nEnter 2 for Medium\nEnter 3 for Hard\n");
            fflush(stdout);
            scanf("%d", &mode);
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}

        printf("Do you want to be player A or B?\n");
        char player;
        scanf("%c", &player);

        if(player == 'B') {
            cond = 1; 
        }
    }
    else
    {
        currentPlayer = playerA;
    }

    printf("\nPlayer A = %c\n", playerA);
    printf("Player B = %c\n\n", playerB);

    //socket
    if (network == 1)
    {
        if (netMode == 's')
        {
            socket_fd = startServer(port);
            printf("Server ready.\n\n");
            fflush(stdout);
        }
        else  // client
        {
            socket_fd = startClient(serverIP, port);
            printf("Client connected.\n\n");
            fflush(stdout);
        }
    }


    while (1)
    {
        print(board, type);

        if (network == 1)
        {
            //server
            if (netMode == 's')
            {
                if (currentPlayer == 'A')  
                {
                    printf("Player A (server), choose column (1-7): ");
                    fflush(stdout); 
                    scanf("%d", &column);
                    sendMove(socket_fd, column);
                }
                else                       
                {
                    printf("Waiting for Player B (client)...\n");
                    column = receiveMove(socket_fd);
                }
            }

            //client
            else if (netMode == 'c')
            {
                if (currentPlayer == 'B')   // client's turn
                {
                    printf("Player B (client), choose column (1-7): ");
                    fflush(stdout); 
                    scanf("%d", &column);
                    sendMove(socket_fd, column);
                }
                else                        // waiting for server
                {
                    printf("Waiting for Player A (server)...\n");
                    fflush(stdout); 
                    column = receiveMove(socket_fd);
                }
            }
        }

        else
        {
            
            printf("Player %c, choose a column (1-7): ", currentPlayer);
            fflush(stdout);

            if(!cond) {

            if (currentPlayer == playerA)
            {
                int status = scanf("%d", &column);

                if (status == 0)
                {
                    printf("\nInvalid! choose another.\n");
                    fflush(stdout); 
                    while (getchar() != '\n');
                    continue;
                }
            }
            else if (currentPlayer == playerB)
            {
                if (mode == 1)
                    column = easyBot(board);
                else if (mode == 2)
                    column = mediumBot(board);
                else if (mode == 3)
                    column = hardBot(board);
                else
                {
                    int status = scanf("%d", &column);

                    if (status == 0)
                    {
                        printf("\nInvalid! choose another.\n");
                        fflush(stdout); 
                        while (getchar() != '\n');
                        continue;
                    }
                }
            }
        } else {

            if (currentPlayer == playerA)
            {
                if (mode == 1)
                    column = easyBot(board);
                else if (mode == 2)
                    column = mediumBot(board);
                else if (mode == 3)
                    column = hardBot(board);
                else
                {
                    int status = scanf("%d", &column);

                    if (status == 0)
                    {
                        printf("\nInvalid! choose another.\n");
                        while (getchar() != '\n');
                        continue;
                    }
                }
            }
            else if (currentPlayer == playerB)
            {

                int status = scanf("%d", &column);

                if (status == 0)
                {
                    printf("\nInvalid! choose another.\n");
                    fflush(stdout); 
                    while (getchar() != '\n');
                    continue;
                }
            }

        }
    }

        
        if (column < 1 || column > 7)
        {
            printf("\nInvalid! choose another.\n");
            fflush(stdout); 
            continue;
        }

        if (!place(board, column, currentPlayer))
        {
            printf("\nColumn full! Choose another.\n");
            fflush(stdout); 
            continue;
        }

        int win = checkWin(board, (64 - currentPlayer) * -1);

        if (win == 1)
        {
            print(board, type);
            printf("Player %c wins!\n", currentPlayer);
            fflush(stdout); 
            break;
        }

        // SWITCH PLAYER
        if (currentPlayer == playerA)
            currentPlayer = playerB;
        else
            currentPlayer = playerA;
    }

    for (int i = 0; i < 6; i++)
        free(board[i]);

    free(board);
}

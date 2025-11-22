#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // toupper
#include "headers.h"

// helper function to read from the other computer 
static int readMove(void){
char buffer[128];
int col = -1;// -1 for invalid move

// while loop(infinite) to keep read from the user until we get the number of  column
while (1){
// reading from user / stdin

// if EOF/ ERROR  return -1(which is invalid input)
if (fgets(buffer, sizeof(buffer), stdin)== NULL){
return -1;
}
for (int i = 0; buffer[i] != '\0'; i++) {
 buffer[i] = toupper((unsigned char)buffer[i]);
}
if (sscanf(buffer, "MOVE %d", &col)==1 || sscanf(buffer, "%d", &col)==1){
    return col;
}
}
}

int networkServer(char current, int** arr){
int col=-1;
// player A 
if (current=='A'){
    while (1){
     printf("Player A (server), enter column (1-7): ");//
        fflush(stdout);    
     if (scanf("%d", &col) != 1) {   // scanf returns 1 when it reads one integer only
        printf("Invalid input. Please enter a number: \n");
        while (getchar() != '\n')   // to remove the other unneeded parts like move
                continue;    
    }
    // send the move to the other computers
    printf("MOVE %d\n", col);        
            fflush(stdout);             // Make sure the message is sent immediately


       return col;
    }

}else {
// player B's turn
    //print it to the client 
    printf("Waiting for Player 2 (client) move...\n");
        fflush(stdout);   
    col = readMove(); // read from the client 
   if (col == -1) {                // -1  error or disconnection
            printf("Connection closed or invalid move received.\n");
        }

    return col;    
 }
}


int networkClient(char current, int** arr){
int col = -1;


    // client = Player  B
    //  the client should ask its LOCAL user
    if (current == 'B') {

        while (1) {                     
            printf("Player 2 (client), enter column (1-7): ");
            fflush(stdout);           
            if (scanf("%d", &col) != 1) {   
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n'){
                    ;
                }

                continue;             
            }

            // Send the move to the server through stdout
            printf("MOVE %d\n", col);
            fflush(stdout);            

            return col;               // Return move so client can update its own board  
        }

    }
    else {
        // the server will send the move to the client

        printf("Waiting for Player 1 (server) move...\n");
        fflush(stdout);                 

        col = readMove();               

        if (col == -1) {                
            printf("Connection closed or invalid move received.\n");
        }

        return col;   

    }

}
#include <stdio.h>
#include "headers.h"

int main() {
    int** arr = createGrid(); 

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++) {
            arr[i][j] = 0; 
        }
    }

    print(arr); 

    for(int i = 0; i < 7; i++) {
        int x = place(arr, 2, 'A'); 

        if(x == 0) {
            printf("Column full\n"); 
            break; 
        }

        print(arr); 
    }


}
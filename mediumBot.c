#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int mediumBot(int **arr){
    int potential[7] = {0};

    //look for potential places to apply move
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            if(arr[i][j]!=0){
                if(j-1>=0) potential[j-1]=1;
                if(j+1<=6) potential[j+1]=1;
            }
        }
    }

    int order[7]={3,2,4,1,5,0,6};

    for(int i=0; i < 7; i++){
        int c = order[i];
        if(!potential[c])
         continue;
        if(arr[0][c]!=0)
         continue;  


        int r=5; 
        
        while(r>=0 && arr[r][c]!=0)
            r--;

        if(r>=0)
            return c+1;                   
    }

    for(int i=0; i<7; i++){
        int c = order[i];
        if(arr[0][c]==0)
         return c+1;
    }

    return 4;
}

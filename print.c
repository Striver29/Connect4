#include <stdio.h>
#include "headers.h"

void print(int **arr, char type)
{

    printf("\n");

    if (type == 'n')
    {
        for (int i = 0; i < 6; i++)
        {
            printf(" ");
            for (int j = 0; j < 7; j++)
            {

                if (arr[i][j] == 0)
                {
                    printf("⚪ "); // empty
                }
                else if (arr[i][j] == 1)
                {
                    printf("🔴 "); // A
                }
                else if (arr[i][j] == 2)
                {
                    printf("🟡 "); // B
                }
            }
            printf("\n");
        }

        printf(" 1  2  3  4  5  6  7\n\n");
    }
    else
    {
        for (int i = 0; i < 6; i++)
        {
            printf(" ");
            for (int j = 0; j < 7; j++)
            {

                if (arr[i][j] == 0)
                {
                    printf(". "); // empty
                }
                else if (arr[i][j] == 1)
                {
                    printf("A "); // A
                }
                else if (arr[i][j] == 2)
                {
                    printf("B "); // B
                }
            }
            printf("\n");
        }

        printf(" 1 2 3 4 5 6 7\n\n");
    }
}
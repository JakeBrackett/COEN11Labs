//
//  DiagonalsEC.c
//  
//
//  Created by Jacob Brackett on 2/4/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#define N 3

void PrintDiagonals(int array[][N], int rows);

int main()
    {
    int array[N][N] = {{1,2,3}, {4,5,6}, {7,8,9}};
    PrintDiagonals(array, N);
    return 0;
    }

void PrintDiagonals(int array[][N], int rows)
    {
    int i;
    for (int diagonal = 0; diagonal < (2 * rows - 1); ++diagonal)
        {
        printf("Diagonal %d: ", diagonal+1);
        if(diagonal < rows)
            {
            for (int i = 0; i <= diagonal; i++)
                {
                printf("%d ", array[diagonal - i][i]);
                }
            }
        else
            {
            for (int i = diagonal - rows + 1; i < rows; i++)
                {
                printf("%d ", array[diagonal - i][i]);
                }
            }
        printf("\n");
        }
    }
    


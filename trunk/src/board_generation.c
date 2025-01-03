#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board_generation.h"

/* oznaczenia pól planszy: e = empty, m = mine, f = flag, u = uncovered */
/* oznaczenia poziomu trudności: 1 = łatwy, 2 = średni, 3 = trudny */
char **CreateBoard (int y, int x, int difficulty) /* jako pierwszy podaje się numer wiersza, a on odpowiada współrzędnej y (dlatego niealfabetyczna kolejność) */
{
    int height, width, mineQuantity;
    char **board;
    switch (difficulty)
    {
    case 1:
        height = 9;
        width = 9;
        mineQuantity = 10;
        break;
        
    case 2:
        height = 16;
        width = 16;
        mineQuantity = 40;
        break;

    case 3:
        height = 16;
        width = 30;
        mineQuantity = 99;
        break;
    
    default:
        break;
    }

    board = malloc (height * sizeof(*board));
    for (int i = 0; i < height; i++)
    {
        board[i] = malloc (width * sizeof(**board));
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            board[i][j] = 'e';
        }
    }
    
    PlaceMines (y, x, height, width, mineQuantity, board);
    return board;
}

void PlaceMines (int y, int x, int height, int width, int mineQuantity, char **board)
{
    srand(time(NULL));
    for (int i = 0; i < mineQuantity; i++)
    {
        int a = rand() % height;
        int b = rand() % width;

        if (board[a][b] == 'e')
        {
            board[a][b] = 'm';
        }
        else i--; /* jeśli trafi na już zaminowane pole to spróbuje znowu */
    }
}

void TestBoardGeneration (int height, int width, char **board)
{
    int i, j, mineCount;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            switch (board[i][j])
            {
            case 'e':
                printf(" .");
                break;

            case 'm':
                printf(" M");
                mineCount++;
                break;
            
            default:
                printf("\n ! SYMBOLE NOT RECOGNIZED ! \n");
                break;
            }
        }
        printf("\n");
    }
    printf("\nHeight: %d \nWidth: %d \nMines: %d \n", i, j, mineCount);
}
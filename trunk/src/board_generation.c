#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board_generation.h"

/* oznaczenia pól planszy: e = empty, m = mine, f = flag, u = uncovered */
/* oznaczenia poziomu trudności: 1 = łatwy, 2 = średni, 3 = trudny */
void SetBoardParameters(int difficulty, board_data_t* data)
{
    data->difficulty = difficulty;
    data->revealedTiles = 0;

    switch (difficulty) {
        case 1: // Easy
            data->height = 9;
            data->width = 9;
            data->mineQuantity = 10;
            break;
        
        case 2: // Medium
            data->height = 16;
            data->width = 16;
            data->mineQuantity = 40;
            break;

        case 3: // Hard
            data->height = 16;
            data->width = 30;
            data->mineQuantity = 99;
            break;

        default: // Invalid difficulty
            data->height = 0;
            data->width = 0;
            data->mineQuantity = 0;
            break;
    }
}

void SetCustomParameters(board_data_t* data)
{
    data->difficulty = 1; // żeby liczyło wynik jako ilość odkrytych * 1
    data->revealedTiles = 0;

    printf("Podaj wysokość planszy: ");
    scanf("%d", &data->height);
    printf("Podaj szerokość planszy: ");
    scanf("%d", &data->width);
    printf("Podaj ilość min: ");
    scanf("%d", &data->mineQuantity);

    if (data->height < 1 || data->width < 1 || data->mineQuantity > data->height * data->width - 1) {
        printf("! Niepoprawne dane. Utworzono planszę o średnim poziomie trudności \n");
        SetBoardParameters(2, data);
    }
}

char **CreateEmptyBoard (board_data_t* data) /* jako 1szy przyjmuje nr wiersza, czyli y (dlatego niealfabetyczna kolejność, tego standardu używa cały program) */
{
    char **board;
    board = malloc (data->height * sizeof(*board));
    for (int i = 0; i < data->height; i++)
    {
        board[i] = malloc (data->width * sizeof(**board));
    }

    for (int i = 0; i < data->height; i++)
    {
        for (int j = 0; j < data->width; j++)
        {
            board[i][j] = 'e';
        }
    }
    
    return board;
}

void PlaceMines (int y, int x, board_data_t* data)
{
    int am;
    srand(time(NULL));
    for (int i = 0; i < data->mineQuantity; i++)
    {
        int a = rand() % data->height;
        int b = rand() % data->width;
        am = 0;
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {

                int ny = y + dy;
                int nx = x + dx;
                if (a == ny && b == nx) {
                    i--;
                    dy = 2;
                    dx = 2;
                    am = 1;
                }
            }
        }
        if (data->board[a][b] == 'e' && am == 0)
        {
            data->board[a][b] = 'm';
        }
        else if (data->board[a][b] == 'm') i--; /* jeśli trafi na już zaminowane pole to spróbuje znowu */
    }
}

board_data_t* ReadBoardFromFile(FILE *in) {

    return NULL;
}

void PrintBoard(board_data_t* data)
{
    for (int i = 0; i < data->height; i++)
    {
        if (i < 10) printf(" "); /* dopóki są jednocyfrowe dopełnia je dodatkową spacją */
        printf(" %d ", i);

        for (int j = 0; j < data->width; j++)
        {
            printf("  ");

            switch (data->board[i][j])
            {
            case 'e': /* puste zakryte pole */
            case 'm': /* mina */
                printf("-");
                break;
            
            case 'f': /* flaga na polu bez miny */
            case 'F': /* flaga na minie */
                printf("F");
                break;
            
            case '1': /* odkryte pole na styku z miną */
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                printf("%c", data->board[i][j]);
                break;

            case 'u': /* odkryte pole wewnętrzne */
                printf(" ");
                break;

            default:
                printf("! Encountered invalid tile description ! \n");
                break;
            }
        }
        printf("\n");
    }

    printf("    ");
    for (int j = 0; j < 10 && j < data->width; j++)  /* dopóki są jednocyfrowe dopełnia je dodatkową spacją */
    {
        printf("  %d", j);
    }
    for (int j = 10; j < data->width; j++)
    {
        printf(" %d", j);
    }
    printf("\n\n");
}

void TestBoardGeneration (board_data_t* data)
{
    printf("\n");
    int mineCount = 0;

    for (int i = 0; i < data->height; i++)
    {
        for (int j = 0; j < data->width; j++)
        {
            switch (data->board[i][j])
            {
            case 'e': /* puste zakryte pole */
                printf(" -");
                break;

            case 'm': /* mina */
                printf(" M");
                mineCount++;
                break;
            
            case 'f': /* flaga na polu bez miny */
                printf(" f");
                break;

            case 'F': /* flaga na minie */
                printf(" F");
                mineCount++;
                break;
            
            case '1': /* odkryte pole na styku z miną */
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                printf(" %c", data->board[i][j]);
                break;
            
            case 'u': /* odkryte pole */
                printf("  ");
                break;

            default:
                printf("! Encountered invalid tile description ! \n");
                break;
            }
        }
        printf("\n");
    }
    printf("\nHeight: %d \nWidth: %d \nDifficulty: %d \nDetected mines: %d \nExpected mines (after 1st valid move): %d \nRevealed tiles: %d \nScore: %d  \n",
        data->height, data->width, data->difficulty, mineCount, data->mineQuantity, data->revealedTiles, GetScore(data));
}


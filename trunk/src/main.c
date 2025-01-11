#include <stdio.h>

#include "board_generation.h"

int main (int argc, char **argv)
{
    int strzalX, strzalY, difficulty;
    printf("Podaj trudność od 1 do 3: ");
    scanf("%d", &difficulty);
    char **board = CreateEmptyBoard(0, 0, difficulty, 0);
    PrintBoard(10, 10, board); // 10 jest tymczasowe
    printf("Podaj X strzału: ");
    scanf("%d", &strzalX);
    printf("Podaj Y strzału: ");
    scanf("%d", &strzalY);
    char **boardWithMines = CreateEmptyBoard(strzalX, strzalX, difficulty, 1);
    PrintBoard(10, 10, boardWithMines);
    return 0;
}
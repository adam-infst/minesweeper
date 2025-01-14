#include <stdio.h>

#include "board_generation.h"
#include "get_input.h"
#include "change_board_state.h"

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
    get_move(stdin); /* tylko po to żeby sprawdzić czy się kompiluje */
    return 0;
}
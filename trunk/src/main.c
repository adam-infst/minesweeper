#include <stdio.h>

#include "board_generation.h"
#include "get_input.h"
#include "update_board_state.h"
#include "board_data_structure.h"

int main (int argc, char **argv)
{
    int difficulty;
    printf("Podaj trudność: (1 = łatwy, 2 = średni, 3 = trudny, 0 = własny) ");
    scanf("%d", &difficulty);

    if (difficulty < 0 || difficulty > 3) {
        printf("! Podano niewłaściwy poziom trudności. Utworzono planszę o trudności 'średni' \n");
        difficulty = 2;
    }

    board_data_t* board_data = init(difficulty);

    PrintBoard(board_data);
    get_move(stdin, board_data);
    PrintBoard(board_data);
    //TestBoardGeneration(board_data);

    FreeBoardData(board_data);
    return 0;
}
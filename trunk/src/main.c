#include <stdio.h>

#include "board_generation.h"
#include "get_input.h"
#include "update_board_state.h"
#include "board_data_structure.h"

int main (int argc, char **argv)
{
    int difficulty;
    printf("Podaj trudność od 1 do 3: ");
    scanf("%d", &difficulty);

    board_data_t* board_data = init(difficulty);

    PrintBoard(board_data);
    get_move(stdin, board_data);
    PrintBoard(board_data);
    TestBoardGeneration(board_data);

    FreeBoardData(board_data);
    return 0;
}
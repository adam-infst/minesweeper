#include <stdio.h>

#include "board_generation.h"

int main (int argc, char **argv)
{
    char **board = CreateBoard(0, 0, 3);
    TestBoardGeneration(16, 30, board);
    return 0;
}
#ifndef BOARD_GENERATION_H
#define BOARD_GENERATION_H
#include "board_data_structure.h"

void SetBoardParameters(int difficulty, board_data_t* data);
void SetCustomParamiters(board_data_t* data);
char **CreateEmptyBoard (board_data_t* data);
void PlaceMines (int y, int x, board_data_t* data);
void TestBoardGeneration (board_data_t* data);
void PrintBoard(board_data_t* data);

#endif

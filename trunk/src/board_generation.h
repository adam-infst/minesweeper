#ifndef BOARD_GENERATION_H
#define BOARD_GENERATION_H
#include <stdbool.h>

char **CreateEmptyBoard (int y, int x, int difficulty, bool mines);
void PlaceMines (int y, int x, int height, int width, int mineQuantity, char **board);
void TestBoardGeneration (int difficulty, char **board);
void PrintBoard(int height, int width, char **board);

#endif

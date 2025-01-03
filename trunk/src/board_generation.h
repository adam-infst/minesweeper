#ifndef _BOARD_GENERATION_H
#define _BOARD_GENERATION_H

char **CreateBoard (int y, int x, int difficulty);
void PlaceMines (int y, int x, int height, int width, int mineQuantity, char **board);
void TestBoardGeneration (int height, int width, char **board);

#endif

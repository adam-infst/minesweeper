#ifndef CHANGE_BOARD_STATE
#define CHANGE_BOARD_STATE
#include <stdbool.h>
#include "board_data_structure.h"

void PutFlag(int y, int x, char **board, bool isMine);
void Reveal(int y, int x, board_data_t* data);
void MakeMove (int y, int x, board_data_t* data, char action);
void DetonateMine();

#endif
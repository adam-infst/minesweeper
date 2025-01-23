#ifndef CHANGE_BOARD_STATE
#define CHANGE_BOARD_STATE
#include <stdbool.h>
#include "board_data_structure.h"

void PutFlag(int y, int x, char **board, bool isMine);
int CountMinesAround(int y, int x, board_data_t* data);
void Reveal(int y, int x, board_data_t* data);
void GetMove (FILE *in, board_data_t* data); /* typ FILE* przyjmuje też stdin */
void MakeMove (int y, int x, board_data_t* data, char action);
bool CheckWinCondition(board_data_t* data);
void DetonateMine();

#endif
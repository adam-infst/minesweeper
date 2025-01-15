#ifndef GET_INPUT_H
#define GET_INPUT_H
#include "board_data_structure.h"

void get_entry_args (int argc, char **argv); /* dopiero szkielet */
void get_move (FILE *in, board_data_t* data); /* typ FILE* przyjmuje też stdin */

#endif
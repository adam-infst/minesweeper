#ifndef BOARD_DATA_STRUCTURE_H
#define BOARD_DATA_STRUCTURE_H

typedef struct {
    int height;
    int width;
    int mineQuantity;
    int revealedTiles;
    int difficulty;
    char **board;
} board_data_t;

board_data_t* init(int difficulty);
int GetScore(board_data_t* data);
void FreeBoardData(board_data_t* data);


#endif
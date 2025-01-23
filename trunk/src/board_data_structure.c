#include <stdio.h>
#include <stdlib.h>

#include "board_data_structure.h"
#include "board_generation.h"

board_data_t* init(int difficulty)
{
    board_data_t* data = malloc(sizeof(board_data_t));
    if (difficulty == 0) {
        SetCustomParamiters(data);
    }
    else {
        SetBoardParameters(difficulty, data);
    }
    data->board = CreateEmptyBoard(data);
    return data;
}

int GetScore(board_data_t* data)
{
    return data->revealedTiles * data->difficulty; 
}

void FreeBoardData(board_data_t* data)
{
    for (int i = 0; i < data->height; i++) /* trzeba najpiew zwolnić poszczególne wiersze */
    {
        free(data->board[i]);
    }
    free(data->board); 
    free(data);
}
#include <stdio.h>
#include <stdbool.h>

#include "update_board_state.h"

void PutFlag(int y, int x, char **board, bool isMine)
{
    if (isMine) board[y][x] = 'F';
    else
        board[y][x] = 'f';
}

int CountMinesAround(int y, int x, board_data_t* data)
{
    int mineCount = 0;
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            if (dy == 0 && dx == 0) continue;

            int ny = y + dy;
            int nx = x + dx;

            if (ny >= 0 && ny < data->height && nx >= 0 && nx < data->width && data->board[ny][nx] == 'm')
            {
                mineCount++;
            }
        }
    }
    return mineCount;
}

void Reveal(int y, int x, board_data_t* data)
{
    if (data->board[y][x] != 'e' && data->board[y][x] != 'f')  return;

    int minesAround = CountMinesAround(y, x, data);

    if (minesAround > 0)
    {
        data->board[y][x] = '0' + minesAround;
    }
    else
    {
        data->board[y][x] = 'u';
        data->revealedTiles++;

        for (int dy = -1; dy <= 1; ++dy)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                if (dy == 0 && dx == 0) continue;

                int ny = y + dy;
                int nx = x + dx;

                if (ny >= 0 && ny < data->height && nx >= 0 && nx < data->width)
                {
                    Reveal(ny, nx, data);
                }
            }
        }
    }
}

void MakeMove (int y, int x, board_data_t* data, char action)
{
    switch (data->board[y][x])
    {
    case 'e':  /* puste zakryte pole */
        if (action == 'f') PutFlag(y, x, data->board, false);
        else
            Reveal(y, x, data);
        break;
    
    case 'm': /* mina */
        if (action == 'f') PutFlag(y, x, data->board, true);
        else 
            DetonateMine();
        break;

    case 'f': /* flaga na polu bez miny */
        if (action == 'f') printf("! Tried to put a flag on a tile that already had a flag !\n");
        else
            Reveal(y, x, data);
        break;

    case 'F': /* flaga na minie */
        if (action == 'f') printf("! Tried to put a flag on a tile that already had a flag !\n");
        else
            DetonateMine();
        break;

    case 'u': /* odkryte pole */
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
        if (action == 'f') printf("! Tried to put a flag on a tile that was already revealed !\n");
        else 
            printf("! Tried to reveal a tile that was already revealed !\n");
        break;

    default:
        printf("! Encountered invalid tile description ! \n");
        break;
    }
}

void DetonateMine()
{
    printf("Zdetonowano mine! Powinienes teraz przegrac ale jeszcze nikt nie zaimplementowal tej funkcji :)\n");
}

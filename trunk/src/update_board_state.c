#include <stdio.h>
#include <stdbool.h>

#include "update_board_state.h"
#include "board_generation.h" // potrzebne do PlaceMines() w GetMove()

void PutFlag(int y, int x, char **board, bool isMine)
{
    if (isMine) board[y][x] = 'F';
    else
        board[y][x] = 'f';
}
bool CheckWinCondition(board_data_t* data) {
    // Check if all non-mine tiles have been revealed or flagged correctly
    for (int y = 0; y < data->height; ++y) {
        for (int x = 0; x < data->width; ++x) {
            // Check if it's a non-mine tile
            if (data->board[y][x] != 'm' && data->board[y][x] != 'M') {
                // If it's still covered (empty or flagged incorrectly), the game is not won
                if (data->board[y][x] == 'e' || data->board[y][x] == 'f') {
                    return false; // There are still hidden tiles
                }
            }
        }
    }
    return true; // All non-mine tiles are either revealed or flagged correctly
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

            if (ny >= 0 && ny < data->height && nx >= 0 && nx < data->width && (data->board[ny][nx] == 'm' || data->board[ny][nx] == 'F'))
                {
                    mineCount++;
                }
        }
    }
    return mineCount;
}

void Reveal(int y, int x, board_data_t* data, int isFirstMove)
{
    if (isFirstMove) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dy == 0 && dx == 0) continue;

                int ny = y + dy;
                int nx = x + dx;
                if (ny >= 0 && ny < data->height && nx >= 0 && nx < data->width && CountMinesAround(ny, nx, data) == 0) {
                    Reveal(ny, nx, data, 0);
                }
            }
        }
    }

    if (data->board[y][x] != 'e' && data->board[y][x] != 'f') {
        return;
    }

    data->revealedTiles++;
    int minesAround = CountMinesAround(y, x, data);

    if (minesAround > 0)
    {
        data->board[y][x] = '0' + minesAround;
    }
    else
    {
        data->board[y][x] = 'u';

        for (int dy = -1; dy <= 1; ++dy)
        {
            for (int dx = -1; dx <= 1; ++dx)
            {
                if (dy == 0 && dx == 0) continue;

                int ny = y + dy;
                int nx = x + dx;

                if (ny >= 0 && ny < data->height && nx >= 0 && nx < data->width)
                {
                    Reveal(ny, nx, data, 0);
                }
            }
        }
    }
}

void GetMove (FILE *in, board_data_t* data)
{
    if (in == stdin) printf("Podaj ruch: ");

    char action;
    int x, y;
    scanf(" %c %d %d", &action, &x, &y);

    if (x < 0 || x > data->width - 1) {
        printf("! There is no such X position on the field !\n");
    }
    else if (y < 0 || y > data->height - 1) {
        printf("! There is no such Y position on the field !\n");
    }
    else if (action == 'f' || action == 'r')
    {
        if (data->revealedTiles == 0) { /* 0 odkrytych pól = to będzie pierwszy ruch */
            PlaceMines(y, x, data);
            MakeMove(y, x, data, action, 1);
        }
        else {
            MakeMove(y, x, data, action, 0);
        }
    }
    else 
        printf("Unknown move '%c'. \nOnly 'f' and 'r' followed by 2 numbers are accepted\n", action);
}

void MakeMove (int y, int x, board_data_t* data, char action, int isFirstMove)
{
    switch (data->board[y][x])
    {
    case 'e':  /* puste zakryte pole */
        if (action == 'f') PutFlag(y, x, data->board, false);
        else
            Reveal(y, x, data, isFirstMove);
        break;
    
    case 'm': /* mina */
        if (action == 'f') PutFlag(y, x, data->board, true);
        else 
            DetonateMine(data->board);
        break;

    case 'f': /* flaga na polu bez miny */
        if (action == 'f') printf("! Tried to put a flag on a tile that already had a flag !\n");
        else
            Reveal(y, x, data, 0);
        break;

    case 'F': /* flaga na minie */
        if (action == 'f') printf("! Tried to put a flag on a tile that already had a flag !\n");
        else
            DetonateMine(data->board);
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

void DetonateMine(char **board)
{
    board[0][0] = 'B';
    printf("Zdetonowano mine!\n");
}

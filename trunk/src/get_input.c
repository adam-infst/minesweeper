#include <stdio.h>
#include <getopt.h>

#include "get_input.h"
#include "board_generation.h"
#include "update_board_state.h"

void get_entry_args (int argc, char **argv)  /* dopiero szkielet */
{
    char c;
    while ((c = getopt(argc, argv, "a")) != -1)
    {
        switch (c)
        {
        case 'a':
            /* code */
            break;
        
        case 'b':
            /* code */
            break;

        default:
            break;
        }
    }
}

void get_move (FILE *in, board_data_t* data)
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
        }
        MakeMove(y, x, data, action);
    }
    else 
        printf("Unknown move '%c'. \nOnly 'f' and 'r' followed by 2 numbers are accepted\n", action);
}


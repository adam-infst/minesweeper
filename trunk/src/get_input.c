#include <stdio.h>
#include <getopt.h>

#include "get_input.h"
#include "change_board_state.h"

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
        
        default:
            break;
        }
    }
}

void get_move (FILE *in)
{
    if (in == stdin) printf("Podaj ruch: ");

    char action;
    int x, y;
    scanf(" %c %d %d", &action, &x, &y);

    if (action == 'f') PutFlag(x, y);

    else if (action == 'r') Reveal(x, y);

    else printf("Unknown move '%c'. \nOnly 'f' and 'r' followed by 2 numbers are accepted\n", action);
}


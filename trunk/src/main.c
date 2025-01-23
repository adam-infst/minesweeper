#include <stdio.h>
#include <getopt.h>
#include "board_generation.h"
#include "update_board_state.h"
#include "board_data_structure.h"

int main (int argc, char **argv)
{
    FILE *in = stdin;
    char c;
    while ((c = getopt(argc, argv, "f:")) != -1)
    {
        if (c == 'f') {
            in = fopen(optarg, "r");

            if (in == NULL) {
                fprintf(stderr, "! Nie udało się znaleźć pliku o podanej nazwie. Program zakończył działanie. \n");
                return -1;
            }
        }
    }

    board_data_t* board_data;

    if (in == stdin) {
        int difficulty;
        printf("Podaj trudność: (1 = łatwy, 2 = średni, 3 = trudny, 0 = własny) ");
        scanf("%d", &difficulty);

        if (difficulty < 0 || difficulty > 3) {
            printf("! Podano niewłaściwy poziom trudności. Utworzono planszę o trudności 'średni' \n");
            difficulty = 2;
        }

        board_data = init(difficulty);
    }
    else {
        board_data = ReadBoardFromFile(in);
    }

    while (board_data->board[0][0] != 'B' && CheckWinCondition(board_data) == 0) // trzeba dodać WARUNEK
    {
        if (in == stdin) {
            PrintBoard(board_data);
            //TestBoardGeneration(board_data);
        }
        printf("_ x y (_ -> f - flag r - reveal)\n");
        GetMove(in, board_data);
        
    }
    GetScore(board_data);
    if(board_data->board[0][0] == 'B')
    {
        printf("BOOM!! Wybuchłeś");
    }
    else
    {
        printf("Brawo! wygrałeś");

    }
    if (in != stdin) {
        fclose(in);     // nwm czy tego nie trzeba będzie osobno w funkcji DetonateMine()
    }
    FreeBoardData(board_data);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include "leaderboard.h"

void SaveScoreToFile(const char* filename, player_score_t player) {
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s %d\n", player.name, player.score);
        fclose(file);
    } else {
        fprintf(stderr, "Nie udało się otworzyć pliku wyniki.txt do zapisu.\n");
    }
}

void LoadScoresFromFile(const char* filename, player_score_t scores[], int* count) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        while (fscanf(file, "%s %d", scores[*count].name, &scores[*count].score) == 2) {
            (*count)++;
        }
        fclose(file);
    } else {
        printf("Plik z wynikami nie istnieje, utworzono nowy.\n");
    }
}

int compareScores(const void* a, const void* b) {
    return ((player_score_t*)b)->score - ((player_score_t*)a)->score;  // Sortowanie malejąco
}

void DisplayTop5Scores(player_score_t scores[], int count) {
    qsort(scores, count, sizeof(player_score_t), compareScores);

    printf("\n5 Najlepszych Graczy:\n");
    int topCount = (count < 5) ? count : 5;
    for (int i = 0; i < topCount; i++) {
        printf("%d. %s - %d\n", i + 1, scores[i].name, scores[i].score);
    }
}
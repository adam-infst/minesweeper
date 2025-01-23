#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <stdio.h>

typedef struct {
    char name[50];  
    int score;     
} player_score_t;


void SaveScoreToFile(const char* filename, player_score_t player);

void LoadScoresFromFile(const char* filename, player_score_t scores[], int* count);

void DisplayTop5Scores(player_score_t scores[], int count);

#endif
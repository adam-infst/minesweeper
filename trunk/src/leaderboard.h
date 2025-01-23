#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <stdio.h>

// Struktura do przechowywania wyniku gracza
typedef struct {
    char name[50];  // Imię gracza
    int score;      // Wynik
} player_score_t;

// Funkcja zapisująca wynik gracza do pliku
void SaveScoreToFile(const char* filename, player_score_t player);

// Funkcja wczytująca wyniki graczy z pliku
void LoadScoresFromFile(const char* filename, player_score_t scores[], int* count);

// Funkcja wyświetlająca 5 najlepszych graczy
void DisplayTop5Scores(player_score_t scores[], int count);

#endif
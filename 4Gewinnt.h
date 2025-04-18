#ifndef CONNECT4_H
#define CONNECT4_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <limits.h>

// Funktionsprototypen
void minimax_bot(SDL_Renderer *renderer);
void suchen_bot(SDL_Renderer *renderer);
void zufaelliger_bot(SDL_Renderer *renderer);
void selbst_spielen(SDL_Renderer *renderer);
void zeichne_spielfeld(SDL_Renderer *renderer);
void mima_vs_bots(char *bot, SDL_Renderer *renderer);
int suche_steine(); 

//MiniMax Logik
int finde_besten_zug(int spieler);
int minimax(int tiefe, bool maximierender_spieler, int spieler, int alpha, int beta);
int bewerten(int spieler);
int bewerten_reihe(int count_spieler, int count_gegner, int leere);

// Konstanten
#define FENSTER_BREITE 700 // Breite vom Fenster
#define FENSTER_HOEHE 600 // Höhe vom Fenster
#define ZEILEN 6 // Anzahl der Zeilen im Spielfeld
#define SPALTEN 7 // Anzahl der Spalten im Spielfeld
#define FELD_GROESSE 100 // Größe eines Spielfelds

#define ROT 1 // Rot = Spieler 1
#define GELB 2 // Gelb = Spieler 2

// Globale Variablen
extern int spielfeld[ZEILEN][SPALTEN]; // Spielfeldmatrix, alles leer
extern int count_turns;
extern int winner;

// Spiellogik
bool setze_stein(int spalte, int spieler);
bool pruefe_gewinner(int spieler);
int suche_steine();

#endif // CONNECT4_H

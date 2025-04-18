#include "4Gewinnt.h"
#include <limits.h>

int count_turns = 0;
int winner = 0;

void mima_vs_bots(char *bot, SDL_Renderer *renderer) {
    bool spiel_laueft = true; // Spielstatus
    int aktueller_spieler = GELB; //Bots beginnen
    int spalte = 0;

    while (spiel_laueft) { 
		if (aktueller_spieler == ROT) {
            		spalte = finde_besten_zug(aktueller_spieler);  // Spalte berechnen
       		} else if (aktueller_spieler == GELB) {
			if(!(strcmp(bot, "random")))
				spalte = rand() % SPALTEN;
			else if(!(strcmp(bot, "search")))
				spalte = suche_steine();
			else if(!(strcmp(bot, "minimax")))
				spalte = finde_besten_zug(aktueller_spieler);
		}
		count_turns++;
		if (count_turns == 42) {
			spiel_laueft = false;
		}
                if (setze_stein(spalte, aktueller_spieler)) { // Stein setzen
                	if (pruefe_gewinner(aktueller_spieler)) { // Gewinn prüfen
				winner = aktueller_spieler;
                        	spiel_laueft = false; // Spiel beenden
                        }
                }
		aktueller_spieler = (aktueller_spieler == ROT) ? GELB : ROT;
        } 
        zeichne_spielfeld(renderer); // Spielfeld aktualisieren	
} 



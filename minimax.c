#include "4Gewinnt.h"
#include <limits.h>

// Bot, der den MiniMax-Algorithmus verwendet
void minimax_bot(SDL_Renderer *renderer) {
    bool spiel_laueft = true; // Spielstatus
    int aktueller_spieler = ROT; // Mensch beginnt

    while (spiel_laueft) { // Hauptspiel-Schleife
        SDL_Event ereignis;

        if (aktueller_spieler == ROT) { // Mensch ist am Zug
            while (SDL_WaitEvent(&ereignis)) { // Auf Ereignisse warten
                if (ereignis.type == SDL_QUIT) { // Spiel beenden
                    spiel_laueft = false;
                    break;
                }

                if (ereignis.type == SDL_MOUSEBUTTONDOWN) { // Maus-Klick
                    int spalte = ereignis.button.x / FELD_GROESSE; // Spalte berechnen
		    //int spalte = finde_besten_zug(aktueller_spieler);
                    if (setze_stein(spalte, aktueller_spieler)) { // Stein setzen
                        if (pruefe_gewinner(aktueller_spieler)) { // Gewinn prüfen
                            printf("Spieler %d gewinnt!\n", aktueller_spieler);
                            spiel_laueft = false; // Spiel beenden
                        }
                        aktueller_spieler = GELB; // Bot ist am Zug
                        break;
                    }
                }
            }
        } else { // Bot ist am Zug
            int spalte = finde_besten_zug(aktueller_spieler); // MiniMax-Logik
            if (setze_stein(spalte, aktueller_spieler)) { // Stein setzen
                if (pruefe_gewinner(aktueller_spieler)) { // Gewinn prüfen
                    printf("Spieler %d gewinnt!\n", aktueller_spieler);
                    spiel_laueft = false; // Spiel beenden
                }
                aktueller_spieler = ROT; // Mensch ist wieder am Zug
            }
        }

        zeichne_spielfeld(renderer); // Spielfeld aktualisieren
    }
}

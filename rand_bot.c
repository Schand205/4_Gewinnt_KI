#include "4Gewinnt.h"

// Bot, der zufällige Züge macht
void zufaelliger_bot(SDL_Renderer *renderer) {
    bool spiel_laueft = true; // Spielstatus
    int aktueller_spieler = ROT; // Startspieler

    while (spiel_laueft) { // Hauptspiel-Schleife
        SDL_Event ereignis;
        while (SDL_PollEvent(&ereignis)) {
            if (ereignis.type == SDL_QUIT) { // Spiel beenden
                spiel_laueft = false;
            }

            if (ereignis.type == SDL_MOUSEBUTTONDOWN) { // Zufallszug
                int spalte = rand() % SPALTEN; // Spalte berechnen
                if (setze_stein(spalte, aktueller_spieler)) { // Stein setzen
                    if (pruefe_gewinner(aktueller_spieler)) { // Gewinn prüfen
                        printf("Spieler %d gewinnt!\n", aktueller_spieler);
                        spiel_laueft = false; // Spiel beenden
                    }
                    aktueller_spieler = (aktueller_spieler == ROT) ? GELB : ROT; // Spieler wechseln
                }
            }
        }

        zeichne_spielfeld(renderer); // Spielfeld aktualisieren
    }
}

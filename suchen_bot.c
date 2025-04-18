#include "4Gewinnt.h"

// Sucht die nächste freie Spalte
int suche_steine() {
	for (int zeile = ZEILEN-1; zeile >= 0; zeile--) {//Suche nach untersten freien Platz mit Nachbarn
		for (int spalte = 0; spalte < SPALTEN; spalte++) {
			if (spielfeld[zeile][spalte] == 0) {
				if (zeile == 0) { //Falls wir uns in der untersten Zeile befinden
					if (spalte == 0 && (spielfeld[zeile][spalte+1] == ROT //Randfälle abdecken
							|| spielfeld[zeile+1][spalte+1] == ROT)) return spalte;
					else if (spalte == 6 && (spielfeld[zeile][spalte-1] == ROT 
							|| spielfeld[zeile+1][spalte-1] == ROT)) return spalte;
					else if (spielfeld[zeile][spalte-1] == ROT || spielfeld[zeile+1][spalte-1] == ROT
						|| spielfeld[zeile][spalte+1] == ROT || spielfeld[zeile+1][spalte+1] == ROT) return spalte;
				}
				else if (spalte == 0) { 
					if (spielfeld[zeile][spalte+1] == ROT || spielfeld[zeile-1][spalte+1] == ROT
							|| spielfeld[zeile+1][spalte+1] == ROT || spielfeld[zeile-1][spalte] == ROT) return spalte;
				} else if (spalte == 6) {
					if (spielfeld[zeile][spalte-1] == ROT || spielfeld[zeile-1][spalte-1] == ROT
							|| spielfeld[zeile+1][spalte-1] == ROT || spielfeld[zeile-1][spalte] == ROT) return spalte;
				} else if (spielfeld[zeile][spalte+1] == ROT || spielfeld[zeile-1][spalte+1] == ROT
					|| spielfeld[zeile+1][spalte+1] == ROT || spielfeld[zeile-1][spalte] == ROT
					|| spielfeld[zeile][spalte-1] == ROT || spielfeld[zeile-1][spalte-1] == ROT
					|| spielfeld[zeile+1][spalte-1] == ROT) return spalte;
			}
		}
	}
	return (rand() % 7); //zufällig, für erste Runde
}


// Bot, der gezielt nach freien Plätzen sucht
void suchen_bot(SDL_Renderer *renderer) {
    bool spiel_laueft = true; // Spielstatus
    int aktueller_spieler = ROT; // Startspieler
    int spalte = 0; // Spalte muss deklariert werden

    while (spiel_laueft) { // Hauptspiel-Schleife
        SDL_Event ereignis; // Ereignisobjekt
        while (SDL_PollEvent(&ereignis)) { // Ereignisse abfragen
            if (ereignis.type == SDL_QUIT) { // Spiel beenden
                spiel_laueft = false;
            }

            if (ereignis.type == SDL_MOUSEBUTTONDOWN) { // Nächster Zug
                if (aktueller_spieler == ROT) {
                    spalte = suche_steine();  // Spalte berechnen
                } else if (aktueller_spieler == GELB) {
                    spalte = rand() % SPALTEN;  // Zufällige Spalte für Gelb
                }

                if (setze_stein(spalte, aktueller_spieler)) { // Stein setzen
                    if (pruefe_gewinner(aktueller_spieler)) { // Gewinner prüfen
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

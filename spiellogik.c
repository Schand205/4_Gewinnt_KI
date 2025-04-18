#include "4Gewinnt.h"

// Stein in Spalte Setzen
bool setze_stein(int spalte, int spieler) {
    for (int zeile = ZEILEN - 1; zeile >= 0; zeile--) { // Suche von unten nach oben
        if (spielfeld[zeile][spalte] == 0) { // Leeres Feld gefunden
            spielfeld[zeile][spalte] = spieler; // Stein setzen
            return true; // Erfolg
        }
    }
    return false; // Spalte ist voll
}

// Prüft, ob der aktuelle Spieler gewonnen hat
bool pruefe_gewinner(int spieler) {
    // Horizontale Gewinnbedingung prüfen
    for (int zeile = 0; zeile < ZEILEN; zeile++) {
        for (int spalte = 0; spalte < SPALTEN - 3; spalte++) {
            if (spielfeld[zeile][spalte] == spieler &&
                spielfeld[zeile][spalte + 1] == spieler &&
                spielfeld[zeile][spalte + 2] == spieler &&
                spielfeld[zeile][spalte + 3] == spieler) {
                return true; // Gewinner gefunden
            }
        }
    }

    // Vertikale Gewinnbedingung prüfen
    for (int zeile = 0; zeile < ZEILEN - 3; zeile++) {
        for (int spalte = 0; spalte < SPALTEN; spalte++) {
            if (spielfeld[zeile][spalte] == spieler &&
                spielfeld[zeile + 1][spalte] == spieler &&
                spielfeld[zeile + 2][spalte] == spieler &&
                spielfeld[zeile + 3][spalte] == spieler) {
                return true; // Gewinner gefunden
            }
        }
    }

    // Diagonale von unten links nach oben rechts prüfen
    for (int zeile = 3; zeile < ZEILEN; zeile++) {
        for (int spalte = 0; spalte < SPALTEN - 3; spalte++) {
            if (spielfeld[zeile][spalte] == spieler &&
                spielfeld[zeile - 1][spalte + 1] == spieler &&
                spielfeld[zeile - 2][spalte + 2] == spieler &&
                spielfeld[zeile - 3][spalte + 3] == spieler) {
                return true; // Gewinner gefunden 
            }
        }
    }

    // Diagonale von oben links nach unten rechts prüfen
    for (int zeile = 0; zeile < ZEILEN - 3; zeile++) {
        for (int spalte = 0; spalte < SPALTEN - 3; spalte++) {
            if (spielfeld[zeile][spalte] == spieler &&
                spielfeld[zeile + 1][spalte + 1] == spieler &&
                spielfeld[zeile + 2][spalte + 2] == spieler &&
                spielfeld[zeile + 3][spalte + 3] == spieler) {
                return true; // Gewinner gefunden 
            }
        }
    }

    return false; // Kein Gewinner
}

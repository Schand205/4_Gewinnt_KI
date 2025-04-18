#include "4Gewinnt.h"
#include <limits.h>

// MiniMax-Logik
// Bewertung für Spieler und Gegner wie gut man steht 
int bewerten_reihe(int count_spieler, int count_gegner, int leere) {
    if (count_spieler == 4) return 10000; // Spieler gewinnt (4 Steine aneinander)
    if (count_gegner == 4) return -10000; // Gegner gewinnt (4 Steine aneinander)
    if (count_spieler == 3 && leere == 1) return 100; // Spieler hat Potenzial zu gewinnen (3 Steine aneinander)
    if (count_gegner == 3 && leere == 1) return -200; // Gegner hat potenziellen zu gewinnen (3 Steine aneinander)
    if (count_spieler == 2 && leere == 2) return 10; // Spieler kann eine Gefahr aufbauen (2 Steine aneinander)
    if (count_gegner == 2 && leere == 2) return -15; // Gegner kann eine Gefahr aufbauen (2 Steine aneinander)
    return 0; // Keine Relevanz
}

int bewerten(int spieler) {
    int bewertung = 0;
    int gegner = (spieler == GELB) ? ROT : GELB;

    // Horizontale Bewertung
    for (int zeile = 0; zeile < ZEILEN; zeile++) {
        for (int spalte = 0; spalte < SPALTEN - 3; spalte++) {
            int count_spieler = 0, count_gegner = 0, leere = 0;
            for (int i = 0; i < 4; i++) {
                if (spielfeld[zeile][spalte + i] == spieler) count_spieler++;
                else if (spielfeld[zeile][spalte + i] == gegner) count_gegner++;
                else leere++;
            }
            bewertung += bewerten_reihe(count_spieler, count_gegner, leere);
        }
    }

    // Vertikale Bewertung
    for (int spalte = 0; spalte < SPALTEN; spalte++) {
        for (int zeile = 0; zeile < ZEILEN - 3; zeile++) {
            int count_spieler = 0, count_gegner = 0, leere = 0;
            for (int i = 0; i < 4; i++) {
                if (spielfeld[zeile + i][spalte] == spieler) count_spieler++;
                else if (spielfeld[zeile + i][spalte] == gegner) count_gegner++;
                else leere++;
            }
            bewertung += bewerten_reihe(count_spieler, count_gegner, leere);
        }
    }

    // Diagonale Bewertung (von unten links nach oben rechts)
    for (int zeile = 3; zeile < ZEILEN; zeile++) {
        for (int spalte = 0; spalte < SPALTEN - 3; spalte++) {
            int count_spieler = 0, count_gegner = 0, leere = 0;
            for (int i = 0; i < 4; i++) {
                if (spielfeld[zeile - i][spalte + i] == spieler) count_spieler++;
                else if (spielfeld[zeile - i][spalte + i] == gegner) count_gegner++;
                else leere++;
            }
            bewertung += bewerten_reihe(count_spieler, count_gegner, leere);
        }
    }

    // Diagonale Bewertung (von oben links nach unten rechts)
    for (int zeile = 0; zeile < ZEILEN - 3; zeile++) {
        for (int spalte = 0; spalte < SPALTEN - 3; spalte++) {
            int count_spieler = 0, count_gegner = 0, leere = 0;
            for (int i = 0; i < 4; i++) {
                if (spielfeld[zeile + i][spalte + i] == spieler) count_spieler++;
                else if (spielfeld[zeile + i][spalte + i] == gegner) count_gegner++;
                else leere++;
            }
            bewertung += bewerten_reihe(count_spieler, count_gegner, leere);
        }
    }

    // Bonus für zentrale Spalten (Mitte ist strategisch wertvoller)
    for (int zeile = 0; zeile < ZEILEN; zeile++) {
        if (spielfeld[zeile][SPALTEN / 2] == spieler) bewertung += 5; // + Bewertung für Spieler in der Mitte
        if (spielfeld[zeile][SPALTEN / 2] == gegner) bewertung -= 5; // - Bewertung für Gegner in der Mitte 
    }

    return bewertung;
}



// Implementiert den MiniMax-Algorithmus mit Alpha-Beta-Pruning (Tiefe ist 5) (Verbesserungsidee: Tiefe Dynamische zur Zeit im Spiel, Tiefe steigt mit Spieldauer)
int minimax(int tiefe, bool maximierender_spieler, int spieler, int alpha, int beta) {
    // Gewinnbedingungen prüfen
    if (pruefe_gewinner(ROT)) return (spieler == ROT) ? 10000 : -10000;
    if (pruefe_gewinner(GELB)) return (spieler == GELB) ? 10000 : -10000;
    
    // Tiefe ist erreicht oder Spielbrett ist voll (Unentschieden)
    bool spielfeld_voll = true;
    for (int spalte = 0; spalte < SPALTEN; spalte++) {
        if (spielfeld[0][spalte] == 0) {
            spielfeld_voll = false;
            break;
        }
    }
    if (tiefe == 0 || spielfeld_voll) {
        return bewerten(spieler);
    }

    // Hier ist Maximierer: Bot-Spieler
    if (maximierender_spieler) {
        int max_bewertung = INT_MIN;
        for (int spalte = 0; spalte < SPALTEN; spalte++) {
            if (spielfeld[0][spalte] == 0) { // Nur freie Spalten prüfen
                setze_stein(spalte, spieler); // Stein setzen

                // Rekursion: Minimierender Spieler am Zug
                int bewertung = minimax(tiefe - 1, false, spieler, alpha, beta);

                // Zug zurücknehmen
                for (int zeile = 0; zeile < ZEILEN; zeile++) {
                    if (spielfeld[zeile][spalte] != 0) {
                        spielfeld[zeile][spalte] = 0;
                        break;
                    }
                }

                max_bewertung = (bewertung > max_bewertung) ? bewertung : max_bewertung;
                alpha = (alpha > max_bewertung) ? alpha : max_bewertung;
                // Alpha-Beta-Pruning
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return max_bewertung;
    } else { //Hier ist  Minimierer: Gegner
        int min_bewertung = INT_MAX;
        int gegner = (spieler == ROT) ? GELB : ROT;
        for (int spalte = 0; spalte < SPALTEN; spalte++) {
            if (spielfeld[0][spalte] == 0) { // Nur freie Spalten prüfen
                setze_stein(spalte, gegner); // Stein setzen

                // Rekursion: Maximierender Spieler am Zug
                int bewertung = minimax(tiefe - 1, true, spieler, alpha, beta);

                // Zug zurücknehmen
                for (int zeile = 0; zeile < ZEILEN; zeile++) {
                    if (spielfeld[zeile][spalte] != 0) {
                        spielfeld[zeile][spalte] = 0;
                        break;
                    }
                }

                min_bewertung = (bewertung < min_bewertung) ? bewertung : min_bewertung;
                beta = (beta < min_bewertung) ? beta : min_bewertung;

                // Alpha-Beta-Pruning
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return min_bewertung;
    }
}

// Findet den besten Zug mit Minimax
int finde_besten_zug(int spieler) {
    int bester_zug = -1;
    int max_bewertung = INT_MIN;

    for (int spalte = 0; spalte < SPALTEN; spalte++) {
        if (spielfeld[0][spalte] == 0) { // Nur freie Spalten prüfen
            setze_stein(spalte, spieler); // Stein setzen

            // Rekursive Bewertung mit Tiefe 5
            int bewertung = minimax(5, false, spieler, INT_MIN, INT_MAX);

            // Zug zurücknehmen
            for (int zeile = 0; zeile < ZEILEN; zeile++) {
                if (spielfeld[zeile][spalte] != 0) {
                    spielfeld[zeile][spalte] = 0;
                    break;
                }
            }

            // Besten Zug aktualisieren
            if (bewertung > max_bewertung) {
                max_bewertung = bewertung;
                bester_zug = spalte;
            }
        }
    }
    return bester_zug;
}



#include "4Gewinnt.h"
#include <time.h>

int spielfeld[ZEILEN][SPALTEN] = {0}; // Spielfeldmatrix, alles leer
// Zeichnet das Spielfeld 
void zeichne_spielfeld(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blau für Hintergrund
    SDL_RenderClear(renderer); // Bildschirm leeren

    for (int zeile = 0; zeile < ZEILEN; zeile++) { // Gehe durch alle Zeilen
        for (int spalte = 0; spalte < SPALTEN; spalte++) { // Gehe durch alle Spalten
            SDL_Rect feld = {spalte * FELD_GROESSE, zeile * FELD_GROESSE, FELD_GROESSE, FELD_GROESSE}; // Spielfeld definieren
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Farbe Blau
            SDL_RenderFillRect(renderer, &feld); // Feld zeichnen

            if (spielfeld[zeile][spalte] == ROT) { // Spieler 1: Rot
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rot
            } else if (spielfeld[zeile][spalte] == GELB) { // Spieler 2: Gelb
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Gelb
            } else { // Weiß für leere Felder
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Weiß
            }

            SDL_Rect viereck = {spalte * FELD_GROESSE + 10, zeile * FELD_GROESSE + 10, FELD_GROESSE - 20, FELD_GROESSE - 20};
            SDL_RenderFillRect(renderer, &viereck); // Viereck zeichnen
        }
    }

    SDL_RenderPresent(renderer); // Renderer aktualisieren
}

// Auswahlmenü für den Spielmodus
void auswahl_menue(SDL_Renderer *renderer) {
    printf("Wählen Sie den Spielmodus:\n");
    printf("1: Random Bot vs. Random Bot\n");
    printf("2: Random Bot vs. Suchen Bot\n");
    printf("3: Mensch vs. MiniMax Bot\n");
    printf("4: Selbst spielen\n");
    printf("Für Loop: ./main random/search/minimax <anzahl_durchläufe>\n");
    int auswahl;
    scanf("%d", &auswahl); // Auswahl einlesen

    switch (auswahl) {
        case 1:
            zufaelliger_bot(renderer); // Zufälliger Bot gegen Zufälliger Bot
            break;
        case 2:
            suchen_bot(renderer); // Zufälliger Bot gegen Suchen-Bot
            break;
        case 3:
            minimax_bot(renderer); // Mensch spielt gegen MiniMax-Bot
            break;
        case 4:
            selbst_spielen(renderer); // Spieler spielt selbst
            break;
        default:
            printf("Ungültige Auswahl. Spiel wird beendet.\n"); // Fehlermeldung bei ungültiger Auswahl
            break;
    }	
}

void auto_loop(int n, char *bot, SDL_Renderer *renderer) {
	if(strcmp(bot, "random") && strcmp(bot, "search") && (strcmp(bot, "minimax"))) {
		fprintf(stderr, "Kein valider Botname!\nrandom / search / minimax\n");
		exit(1);
	}
	int sum_turns = 0;
	int mimawins = 0;
	for(int i = 0; i < n; i++) {
		//zurücksetzen des Spielfeldes
		for(int zeile = 0; zeile < ZEILEN; zeile++) 
			for(int spalte = 0; spalte < SPALTEN; spalte++) 
				spielfeld[zeile][spalte] = 0;
		zeichne_spielfeld(renderer);
		mima_vs_bots(bot, renderer);
		sum_turns = sum_turns + count_turns;
		if(winner == ROT) mimawins++;
		count_turns = 0;
		winner = 0;
	}
	float avg_turns = (float)sum_turns/n;
	printf("Minimax gegen %s:\nDurchgänge: %d\nDurchschnittliche Anzahl der Züge: %.2f\nMinimax Wins: %d/%d\n", bot, n, avg_turns, mimawins, n);
}		

// Haupteinstiegspunkt des Programms
int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO); // SDL initialisieren
	SDL_Window *fenster = SDL_CreateWindow("4 Gewinnt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, FENSTER_BREITE, FENSTER_HOEHE, SDL_WINDOW_SHOWN); // Fenster erstellen
	SDL_Renderer *renderer = SDL_CreateRenderer(fenster, -1, SDL_RENDERER_ACCELERATED); // Renderer erstellen
	
	srand(time(NULL));

	int n = 0;
	if(argc == 3) {
		char *bot = argv[1];
		n = atoi(argv[2]);
		auto_loop(n, bot, renderer);
	}
	else {
		auswahl_menue(renderer); // Spielmodus auswählen
	}


	SDL_DestroyRenderer(renderer); // Renderer löschen
	SDL_DestroyWindow(fenster); // Fenster löschen
	SDL_Quit(); // SDL beenden
			

	return 0; // Erfolgreiches Beenden
}

# 4 Gewinnt mit Minimax-Implementierung

Dieses Projekt ermöglicht es, **"Vier Gewinnt"** in verschiedenen Varianten zu spielen. Dabei können ein oder zwei Benutzer über eine grafische Benutzeroberfläche, basierend auf **SDL2**, gegeneinander antreten. Zusätzlich gibt es die Möglichkeit, mehrere automatisierte Spieldurchläufe zu simulieren, in denen die von uns entwickelten Bots gegeneinander antreten. Die Ergebnisse dieser Simulationen werden ausgegeben, um eine fundierte Analyse und Bewertung der Strategien zu ermöglichen.

---

## Voraussetzungen

Für die Ausführung des Projekts wird **SDL2** benötigt. Die Installation hängt von der verwendeten Linux-Distribution ab und wird im nächsten Abschnitt beschrieben.

---

## Installation von SDL2 auf Linux

### Installation über den Paketmanager

#### **Debian/Ubuntu-basierte Systeme**
Führe die folgenden Befehle im Terminal aus, um SDL2 zu installieren:

```bash
sudo apt update
sudo apt install libsdl2-dev
```

Falls zusätzliche Module benötigt werden, installiere diese mit:
```bash
sudo apt install libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

## Projektstruktur

Das Projektverzeichnis enthält folgende Dateien:

- `4Gewinnt.c`: Hauptprogrammdatei, in der das Spiel und das Anfangsmenü gestartet wird.
- `4Gewinnt.h`: Header-Datei des Programms.
- `loop_logik.c`: Spiellogik der Schleifenausführung von Bot gegen Bot.
- `minimax_logik.c`: Implementierung des Minimax-Algorithmus und Alpha-Beta-Pruning.
- `minimax.c`: Enthält Spiellogik, die die Minimax-Logik aus `minimax_logik.c` verwendet.
- `rand_bot.c`: Logik für den Bot, der zufällige Spielzüge durchführt.
- `selbst_spielen.c`: Logik, die das Spielen durch einen Benutzer ermöglicht.
- `spiellogik.c`: Allgemeine Spiellogik für das Setzen von Steinen und die Überprüfung eines Gewinners.
- `suchen_bot.c`: Bot-Logik, die nach einem gleichfarbigen Stein sucht und daneben einen Stein einwirft.
- `Makefile`: Datei zur automatisierten Kompilierung und Verlinkung aller Quellcodedateien.

## Ausführung

Das Projekt verwendet ein Makefile, um die Quellcodedateien zu verlinken und das Programm zu bauen.

### Kompilieren und Starten des Programms
1. Öffne ein Terminal im Projektverzeichnis.
2. Kompiliere das Projekt mit folgendem Befehl:
make
3. Starte das Programm mit:

```bash
./main
```

## Automatisierte Spieldurchläufe
Das Programm bietet die Möglichkeit, mehrere Spieldurchläufe zu simulieren, bei denen ein Bot gegen den Minimax-Algorithmus antritt. Um eine Simulation zu starten, verwende folgenden Befehl:

```bash
./main <Bot-Name> <Anzahl der Durchläufe>
```

Gültige Bot-Namen:

random – Der Zufalls-Bot wählt seine Züge ohne Strategie.
search – Der Such-Bot nutzt einfache Heuristiken.
minimax – Der Minimax-Bot plant strategische Züge im Voraus.
Beispiel: Um den random-Bot gegen den Minimax-Bot in 100 Durchläufen antreten zu lassen, gib folgenden Befehl ein:
```bash
./main random 100
```


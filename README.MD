# Snake

Un classico gioco Snake realizzato in C++ con interfaccia testuale tramite ncurses.

## Descrizione

Questo progetto implementa il gioco Snake, dove il giocatore controlla un serpente che cresce mangiando mele e deve evitare di scontrarsi con se stesso. Il gioco offre un menu, diversi livelli di difficoltà, una classifica dei punteggi e un timer.

## Struttura del progetto

- `main.cpp`: punto di ingresso del programma.
- `Game.hpp/cpp`: logica principale del gioco, gestione degli stati e delle schermate.
- `Menu.hpp/cpp`: gestione del menu principale, selezione livelli e opzioni.
- `Board.hpp/cpp`: gestione della finestra di gioco e delle operazioni di disegno.
- `Snake.hpp/cpp`: logica del serpente (movimento, collisioni, crescita).
- `Apple.hpp/cpp`: gestione delle mele.
- `Scriba.hpp/cpp`: gestione della classifica e salvataggio punteggi.
- `Const.hpp`: costanti di configurazione (dimensioni, limiti, ecc).
- `Position.hpp`: struttura per rappresentare le coordinate.
- `classifica.txt`: file di testo per la classifica.
- `Makefile`: per compilare il progetto su sistemi Unix-like.

## Requisiti

- **C++ Compiler**: g++ (Linux/macOS), MinGW-w64 (Windows)
- **Libreria ncurses**:
  - **Linux**: `ncursesw` (ampio supporto Unicode)
  - **macOS**: `ncurses` (già presente, ma si consiglia di aggiornarla con Homebrew)
  - **Windows**: [PDCurses](https://pdcurses.org/) (alternativa a ncurses)

## Istruzioni per l'installazione e l'esecuzione

### Linux

1. **Installa le dipendenze**:
   ```sh
   sudo apt update
   sudo apt install g++ libncursesw5-dev make
   ```
2. **Compila il progetto**:
   ```sh
   make
   ```
3. **Esegui il gioco**:
   ```sh
   ./main
   ```

### macOS

1. **Installa Homebrew** (se non lo hai già):
   ```sh
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```
2. **Installa ncurses**:
   ```sh
   brew install ncurses
   ```
3. **Compila il progetto** (specificando il path di ncurses se necessario):
   ```sh
   make
   ```
   Se hai errori relativi a ncurses, prova:
   ```sh
   g++ main.cpp Board.cpp Game.cpp Apple.cpp Snake.cpp Menu.cpp Scriba.cpp -lncurses -I/usr/local/opt/ncurses/include -L/usr/local/opt/ncurses/lib -o main
   ```
4. **Esegui il gioco**:
   ```sh
   ./main
   ```

### Windows

1. **Scarica e installa [MinGW-w64](https://www.mingw-w64.org/)** per avere `g++`.
2. **Scarica e installa [PDCurses](https://pdcurses.org/)** (versione per Windows di ncurses).
3. **Compila il progetto** (adattando il comando per includere i file header e le librerie di PDCurses):
   ```sh
   g++ main.cpp Board.cpp Game.cpp Apple.cpp Snake.cpp Menu.cpp Scriba.cpp -lpdcurses -o main.exe
   ```
   Assicurati che i file `.h` e `.lib` di PDCurses siano nel path corretto.
4. **Esegui il gioco**:
   ```sh
   main.exe
   ```

## Comandi di gioco

- Usa le frecce direzionali per muovere il serpente.
- Premi `M` per tornare al menu durante la partita.
- Nel menu, usa le frecce e Invio per selezionare le opzioni.

## Funzionalità

- **Livelli di difficoltà**: facile, medio, difficile.
- **Classifica**: i punteggi vengono salvati e visualizzati.
- **Timer**: tempo limite per ogni partita.
- **Menu di morte**: possibilità di tornare al menu o uscire.

## Note

- Su Windows, la compatibilità grafica e dei tasti può variare a seconda del terminale usato.
- Su macOS, se riscontri problemi con ncurses, assicurati di usare la versione aggiornata tramite Homebrew.
- La classifica viene salvata nel file `classifica.txt` nella cartella del gioco.

## Autore

Andrea Di Dio
Mattia Sergio
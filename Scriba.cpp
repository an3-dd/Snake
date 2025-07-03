#include "Scriba.hpp"
#include "Const.hpp"
#include "Position.hpp"
#include <ncurses.h>


Scriba::Scriba(){
    initBoard();
};

void Scriba::initBoard(){
    scoreBoard.init();
}


int Scriba::getCount(){
    return this->count;
}


void Scriba::sortScores() {
    for (int i = 0; i < MAX_SCORES - 1; i++) {
        for (int j = 0; j < MAX_SCORES - i - 1; j++) {
            if (scores[j].points < scores[j+1].points) {
                ScoreEntry temp = scores[j];
                scores[j] = scores[j+1];
                scores[j+1] = temp;
            }
        }
    }
}


void Scriba::saveScore(int points, const char* level) {

    // apre il file in modalita append (senza cancellare il suo contenuto ios::app)
    ofstream ofs("classifica.txt", ios::app);
    if (!ofs) {
        cerr << "Errore nell'aprire il file per scrivere\n";
        return;
    }

    // se non si verificano errori, scrive in ofs, points "modalità: " level 
    ofs << points << " " << level << "\n";
}


void Scriba::showScores() {
    ifstream ifs("classifica.txt");
    if (!ifs) {
        cerr << "Errore nell'aprire il file per leggere\n";
        return;
    }

    // Inizializzo scores
    for (int i = 0; i < MAX_SCORES; ++i) {
        scores[i].points = 0;
        scores[i].level[0] = '\0';
    }

    char line[100];
    int count = 0;

    while (count < MAX_SCORES && ifs.getline(line, sizeof(line))) {
        if (line[0] == '\0') continue;  // salto righe vuote

        // Cerco il primo spazio per separare punti e livello
        char* spacePos = strchr(line, ' ');
        if (!spacePos) continue; // se non c'è spazio salto

        // Divido la stringa in due: 
        *spacePos = '\0';  // fine punteggio
        char* ptsStr = line;
        char* lvlStr = spacePos + 1;

        // Converto punti a int
        int pts = atoi(ptsStr);

        // Copio il livello in modo sicuro
        strncpy(scores[count].level, lvlStr, 49);
        scores[count].level[49] = '\0';

        scores[count].points = pts;

        count++;
    }

    sortScores();

    scoreBoard.clear();

    Position pos;
    for (int i = 0; i < count; i++) {
        pos.x = WIDTH / 2;
        pos.y = (HEIGHT - count) / 2 + i;

        char strMatch[100];
        snprintf(strMatch, sizeof(strMatch), "%d punti - Livello: %s", scores[i].points, scores[i].level);
        scoreBoard.addStringAt(pos, strMatch);
    }

    Position adv;
    adv.x = 2;
    adv.y = 3;

    char menu[] = {"premi qualsiasi tasto per tornare al menu \n"};
    char reset[] = {" oppure premi c per resettare tutta la classifica"};

    


    scoreBoard.addStringAt(adv, menu);
    adv.y++;

    scoreBoard.addStringAt(adv, reset);

    scoreBoard.addBorder();

    scoreBoard.refresh();

    // Aspetta input dell'utente per tornare al menu
    int c = scoreBoard.getInput();

    if (c == 'c' || "C"){
        cleanPodium();
    }
}

void Scriba::cleanPodium() {
    ofstream ofs("classifica.txt", ios::trunc);  // apertura in modalità truncate che cancella l'intero contenuto del file
    if (!ofs) {
        cerr << "Errore nell'aprire il file per la pulizia\n";
        return;
    }
    ofs.close();
}





#include "Scriba.hpp"
#include "Const.hpp"
#include "Position.hpp"
#include <cstdio>
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

void Scriba::showScores() {

    scoreBoard.clear();

    std::ifstream ifs("classifica.txt");
    if (!ifs.is_open()) return;

    char line[RAW_LEN];
    Position center;
    center.y = 1;

    while (ifs.getline(line, RAW_LEN)) {
        int len = std::strlen(line);
        Position pos = { (WIDTH - len) / 2, center.y++ };
        scoreBoard.addStringAt(pos, line);
    }

    // messaggi finali
    center.y += 2;
    scoreBoard.addStringAt({(WIDTH - 42) / 2, center.y++}, (char*)"premi qualsiasi tasto per tornare al menu");
    scoreBoard.addStringAt({(WIDTH - 45) / 2, center.y++}, (char*)"oppure premi c per resettare tutta la classifica");

    refresh();


    int c = scoreBoard.getInput();

    if (c == 'c' || c == 'C') {
        cleanPodium();
        refresh();
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


// funzione che inserisce pts e level nell'array righe contenente tutte le righe presenti nel file
void Scriba::insertRec(char righe[][RAW_LEN], int pos, int pts, const char level[]){

    if (pos >= MAX_RAW || righe[pos][0] == '\0'){
        // inserisce all'interno di una riga (righe[pos]) la stringa "punti livello"
        snprintf(righe[pos], RAW_LEN, "%d %s", pts, level);
        return;
    }

    // riga corrente
    char *p = righe[pos];

    // punteggio estratto dalla riga corrente (p)
    int currPts = strtol(p, nullptr, 10);

    if (pts > currPts){

        // sposta tutte le righe successivo in basso per creare spazio al nuovo punteggio
        for (int i = MAX_RAW - 1; i > pos; --i) strcpy(righe[i], righe[i-1]);
        // inserice in righe[pos] il risultato che volevamo aggiungere
        snprintf(righe[pos], RAW_LEN, "%d %s", pts, level);
        return;
    }

    // richima ala funzione sulla riga successiva
    insertRec(righe, pos + 1, pts, level);
}


void Scriba::insert(int pts, const char level[]){

    char righe[MAX_RAW][RAW_LEN] = {{0}};
    int count = 0;

    // lettura del file esistente
    ifstream ifs("classifica.txt");


    while (count < MAX_RAW){

        // se non si riesce a estrapolare una riga -> siamo arrivati alla fine del file
        // la funzione getline legge anche le righe vuote, quindi non si blocca quando ne trova una
        if (!ifs.getline(righe[count], RAW_LEN)){
            break;
        }
        // se la riga letta non è vuota allora incrementa count
        if (righe[count][0] != '\0'){
            count++;
        }
    }
    ifs.close();

    insertRec(righe, 0, pts, level);


    // puliamo il file attuale
    cleanPodium();


    // sovrascriviamo il file con il nuovo contenuto
    ofstream ofs("classifica.txt");
    for (int i = 0; i < MAX_RAW && righe[i][0] != '\0'; i++) ofs << righe[i] << '\n';
    ofs.close();
}



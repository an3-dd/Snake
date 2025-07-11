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

void Scriba::showScores() {

    scoreBoard.clear();

    std::ifstream ifs("classifica.txt");
    if (!ifs.is_open()) return;

    char line[ROW_LEN];
    Position center;
    center.y = 1;

    while (ifs.getline(line, ROW_LEN)) {
        int len = std::strlen(line);
        Position pos = { (WIDTH - len) / 2, center.y++ };
        scoreBoard.addStringAt(pos, line);
    }

    // final message
    center.y += 2;
    scoreBoard.addStringAt({(WIDTH - 40) / 2, center.y++}, (char*)"PREMI QUALUNQUE TASTO PER TORNARE AL MENU");
    scoreBoard.addStringAt({(WIDTH - 26) / 2, center.y++}, (char*)"PREMI C PER PULIRE IL PODIO");
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


// function that inserts pts and level into the array righe containing all the lines present in the file
void Scriba::insertRec(char righe[][ROW_LEN], int pos, int pts, const char level[]){
    if (pos >= MAX_ROW) {
        // classifica piena, non inserire nulla
        return;
    }
    if (righe[pos][0] == '\0'){
        snprintf(righe[pos], ROW_LEN, "%d %s", pts, level);
        return;
    }

    // current line
    char *p = righe[pos];

    // score extracted from the current line (p)
    int currPts = strtol(p, nullptr, 10);

    if (pts > currPts){

        // shift all subsequent lines down to make room for the new score
        for (int i = MAX_ROW - 1; i > pos; --i) strcpy(righe[i], righe[i-1]);
        // insert in righe[pos] the result we wanted to add
        snprintf(righe[pos], ROW_LEN, "%d %s", pts, level);
        return;
    }

    // call the function on the next line
    insertRec(righe, pos + 1, pts, level);
}


void Scriba::insert(int pts, const char level[]){

    char righe[MAX_ROW][ROW_LEN] = {{0}};
    int count = 0;

    // reading the existing file
    ifstream ifs("classifica.txt");


    // if we can't extract a line -> we've reached the end of the file
    // the getline function also reads empty lines, so it doesn't get stuck when it finds one
    while (count < MAX_ROW && ifs.getline(righe[count], ROW_LEN)){
        // se la riga letta non è vuota allora incrementa count
        if (righe[count][0] != '\0'){
            count++;
        }
    }
    ifs.close();

    insertRec(righe, 0, pts, level);


    // clean the current file
    cleanPodium();


    // overwrite the file with the new content
    ofstream ofs("classifica.txt");
    for (int i = 0; i < MAX_ROW && righe[i][0] != '\0'; i++) ofs << righe[i] << '\n';
    ofs.close();
}



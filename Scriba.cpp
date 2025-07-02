#include "Scriba.hpp"
#include "Const.hpp"
#include "Position.hpp"
#include <cstdio>


Scriba::Scriba(){
    scoreBoard.init();
};


int Scriba::getCount(){
    return this->count;
}


void Scriba::sortScores() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
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
    ofs << points << "   modalità: " << level << "\n";
}


void Scriba::showScores() {

    // apre il file classifica.txt
    ifstream ifs("classifica.txt");
    if (!ifs) {
        cerr << "Errore nell'aprire il file per leggere\n";
        return;
    }

    int count = 0;
    int pts;
    char lvl[50];

    // usa l'operatore di estrazione >> per leggere cio che 
    // si trova in quella riga del file e metterlo nelle variabili
    // il ciclo si interrompe quando non riesce a leggere punteggio o livello]
    while (ifs >> pts >> lvl) {
        if (count < MAX_SCORES) {
            scores[count].points = pts;
            strncpy(scores[count].level, lvl, 49);
            scores[count].level[49] = '\0';
            count++;
        }
    }


    // ordina mediante bubblesort tutti i pinteggi
    // che sono stati memorizzati all'interno dell'array di scores
    sortScores();

    //for (int i = count - 1; i >= 0; i++){
    int i = 0;
        Position center;
        Position pos;
        center.x = WIDTH/2;
        center.y = HEIGHT/2;
        pos.x = center.x;
        pos.y = (HEIGHT - count) / 2 + i;

        // creazione della stringa che voglio aggiungere
        //// estrapolandola dall'array scores che prende le informazioni da classifica.txt
        //char puntiLivello[] = " punti - Livello: ";
        //char strMatch[49] = strcat((char)scores[i].points, puntiLivello, (char[])scores[i].level);
        char strMatch[100];
        sprintf(strMatch, "%d punti - Livello: %s", scores[i].points, scores[i].level);
        this->scoreBoard.addStringAt(center, strMatch);
        printf("\n");


    //}
    scoreBoard.clear();
    scoreBoard.refresh();


    /*
  Position center;
  Position pos;
  center.x = WIDTH/2;
  center.y = HEIGHT/2; 
  keypad(menuBoard.getWin(), TRUE);
  curs_set(0);
  while (1){
    menuBoard.clear();
    for (int i = 0; i < numVoices; i++){
      pos.x = center.x;
      pos.y = (HEIGHT - numVoices) / 2 + i;
      if (i == selected){
        wattron(menuBoard.getWin(), A_REVERSE);
        menuBoard.addStringAt(pos, voices[i]);
        wattroff(menuBoard.getWin(), A_REVERSE);
      }
      else menuBoard.addStringAt(pos, voices[i]);
    }
    menuBoard.refresh();*/


//    cout << "Classifica punteggi:\n";
//    for (int i = 0; i < i; i++) {
//        cout << i << " " << scores[i].points << " punti - Livello: " << scores[i].level << "\n";
//    }





    
}
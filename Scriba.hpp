#include <fstream>
#include <iostream>
#include <cstring>
#include "Board.hpp"




using namespace std;



struct ScoreEntry {
    int points;
    char level[50];
};




class Scriba {


protected:


    static const int MAX_SCORES = 100;
    Board scoreBoard;


    // l'array scores tiene un massimo di punteggi che la classifica puo immagazzinare
    // la variabile coutn, ci dice quanti ce ne sono memorizzati al momento
    ScoreEntry scores[MAX_SCORES];
    int count = 0;


    // semplice bubble sort decrescente per points
    void sortScores();


    

public:


    // costruttore
    Scriba();

    int getCount();

    // funzione che salva le score all'interno del file classifica.txt
    // mediante l'uso di ofstream
    void saveScore(int points, const char* level);



    // funzione che mostra i dati salvati all'interno del file classifica.txt
    // mediante l'uso di ifstream
    void showScores();


};



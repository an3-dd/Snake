#include <fstream>
#include <iostream>
#include <cstring>
#include "Board.hpp"
#include "Const.hpp"


using namespace std;



class Scriba {


protected:

    Board scoreBoard;

public:


    // costruttore
    Scriba();

    // rimuove il contenuto del file
    void cleanPodium();

    // inizializza scoreBoard
    void initBoard();

    // funzione ausiliaria di insert
    void insertRec(char righe[][ROW_LEN], int pos, int pts, const char level[]);

    // inserisce una riga contenente il punteggio e il livello in modo ordinato dentro la classifica.txt 
    void insert(int pts, const char level[]);

    // mostra i dati salvati all'interno del file classifica.txt
    // mediante l'uso di ifstream
    void showScores();


};



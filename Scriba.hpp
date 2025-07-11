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


    // constructor
    Scriba();

    // removes the content of the file
    void cleanPodium();

    // initializes scoreBoard
    void initBoard();

    // auxiliary function for insert
    void insertRec(char righe[][ROW_LEN], int pos, int pts, const char level[]);

    // inserts a line containing the score and level in an ordered manner into the classifica.txt
    void insert(int pts, const char level[]);

    // shows the data saved inside the file classifica.txt
    // using ifstream
    void showScores();


};



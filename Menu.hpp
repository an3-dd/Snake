#pragma once

#include "Board.hpp"
#include "Scriba.hpp"




struct Levels {
    char name[30];
    int diff;
    int bonus;
    int timeSec = 60;
    Levels *next;
    Levels *prev;

    // è possibile anche inserire un costruttore all'interno della struttura 

    // anche se il tempo del livello non è terminato deve essere possibile 
    // cambiare livello durante la sua esecuzione
};

/*
struct Player{
    char nickname[50];
    int score;
    int position;
};
*/


class Menu{


    protected:

    Scriba scriba;
    Board menuBoard;
    // Player player;
    Levels *level;
    int choice = -1;
    bool isOpen;



    public:

    Menu(int height, int width);

    void initBoard();

    void open();

    void close();

    void goUp();

    void goDown();

    int getChoice();

    // init level's list
    void initLevels();

    // return the choice
    int select();

    void selectLevel();

    void viewPodium();

    
    // remove all players and score
    void cleanPodium();


    void addScore(char name[]);

    // set the nickname and initialize score to 0
    // void createPlayer(char c[]);

    // void setName();



};
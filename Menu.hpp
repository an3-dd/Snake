#pragma once

#include "Board.hpp"




struct Levels {
    char name[30];
    int diff = 0;
    int bonus = 0; // bisogna assegnare unvalore di default
    int timeSec = 60;
    Levels *next;
    Levels *prev;
};




class Menu{


    protected:

    // Scriba scriba;

    // genera una finestra, è un costruttore di una board
    Board menuBoard;

    Levels *head = nullptr;
    Levels currentLevel;
    int choice = -1;
    int level = -1;
    bool isOpen;




    // add 3 default levels in the level's list
    void initLevels();

    public:

    Menu();

    // print options in the menu board (play, view stats ...)
    // questa funzione al termine della sua esecuzione setta il parametro
    // choice in base alla voce sulla quale è stato premuto invio
    void showOptions();

    int getLevel();

    void startGame();

    void showScore();

    void exitGame();

    // add a level in the list
    bool addLevel(int d, char name[]);

    // print all levels in the list
    void printLevels();

    void initBoard();

    void open();

    void close();

    void goUp();

    void goDown();

    int getChoice();

    void showLevels();

    void viewPodium();

    // cerca il livello con la difficolta = diff
    // copia in currentLevel il livello trovato
    void setCurrentLevel(int diff);

    Levels getCurrentLevel();

    // clean classifica.txt
    // void cleanPodium();

    void addScore(char name[]);

    // set the parameter choice to -1
    void resetChoice();


};
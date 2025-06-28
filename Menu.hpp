#pragma once

#include "Board.hpp"
#include "Scriba.hpp"




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

    Scriba scriba;
    Board menuBoard;
    Levels *head;
    Levels *currentLevel;
    int choice = -1;
    bool isOpen;



    public:

    Menu();

    // add a level in the list
    bool addLevel(int d, char name[]);

    // print all levels in the list
    void printLevels();

    void initBoard();

    // add an option to the menu board (play, view stats ...)
    void addVoices();

    void open();

    void close();

    void goUp();

    void goDown();

    int getChoice();

    // add 3 default levels in the level's list
    void initLevels();

    void selectLevel();

    void viewPodium();

    // clan classifica.txt
    void cleanPodium();

    void addScore(char name[]);



};
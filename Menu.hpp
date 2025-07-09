#pragma once

#include "Board.hpp"




struct Levels {
    char name[30];
    int diff = 0;
    Levels *next;
    Levels *prev;
};




class Menu{


    protected:

    // board del menu
    Board menuBoard;
    // testa della lista dei livelli del menu
    Levels *head = nullptr;
    Levels currentLevel;
    int choice = -1;




    // add 3 default levels in the level's list
    void initLevels();

    public:

    Menu();
    ~Menu();

    void setCurrentLevel();

    Levels getCurrentLevel();

    Board getMenuBoard();

    // mostra le opzioni selezionabili
    void showOptions();

    // mostra le opzioni selezionabili nel menu di morte
    void showDeathOptions();

    void openDeath();

    // add a level in the list
    bool addLevel(int d, char name[]);

    void initBoard();

    void open();

    int getChoice();

    void showLevels();

    // cerca il livello con la difficolta = diff
    // copia in currentLevel il livello trovato
    void setCurrentLevel(int diff);

    // set the parameter choice to -1
    void resetChoice();



};
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

    Board menuBoard;
    Levels *head = nullptr;
    Levels currentLevel;
    int choice = -1;



    public:

    Menu();
    ~Menu();

    // add 3 default levels in the level's list
    void initLevels();

    void setCurrentLevel();

    Levels getCurrentLevel();

    Board getMenuBoard();

    // show menu options
    void showOptions();

    // show selectable options in the death menu
    void showDeathOptions();

    // clear the menu board and show the options
    void open();

    // clear the menu board and show the endgame's options
    void openDeath();

    // add a level in the list
    bool addLevel(int d, char name[]);

    void initBoard();

    int getChoice();

    void showLevels();

    // find the level with difficulty = diff
    // copy the found level into currentLevel
    void setCurrentLevel(int diff);

    // set the parameter choice to -1
    void resetChoice();



};
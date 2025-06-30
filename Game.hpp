#pragma once

#include <ncurses.h>
#include "Const.hpp"
#include "Board.hpp"
#include "Apple.hpp"
#include "Snake.hpp"

//for the randomizer
#include "cstdlib"
#include "ctime"

class Game{


    protected:

    Board board;
    Position center;
    bool gameOver;
    Apple apple[10]; //there are 10 apples on the screen, when one is eaten it respawns in another point
    Snake snake;

    public:

    Game();

    //Board logic

    Board getBoard();

    void openMenu();

    void processInput();

    void updateState();

    bool isOver();


    //Apple methods

    Position randomPosition();

    void printApple(Position p);

    void removeApple(Position p);
    

    //Snake methods

    void initPrintSnake();

    void updateSnake(Direction inputDirection);

};



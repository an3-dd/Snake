#pragma once

#include <ncurses.h>
#include "Board.hpp"
#include "Apple.hpp"

class Game{


    protected:

    Board board;
    bool gameOver;
    Apple apple;

    public:

    Game(int height, int width);

    // return the game's board heigth
    int getHeight();

    // return the game's board width
    int getWidth();

    void processInput();

    void updateState();

    void redraw();

    bool isOver();


};



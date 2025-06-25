#pragma once

#include <ncurses.h>
#include "Board.hpp"
#include "Apple.hpp"

class Game{


    protected:

    Board board;
    bool gameOver;
    // Snake snake;

    public:

    Game(int height, int width);

    // retunr the game's board heigth
    int getHeight();

    // return the game's board width
    int getWidth();

    void processInput();

    void updateState();

    void redraw();

    bool isOver();


};



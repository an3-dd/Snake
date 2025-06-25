#pragma once

#include <ncurses.h>
#include "Board.hpp"
#include "Apple.hpp"

//for the randomizer
#include "cstdlib"
#include "ctime"

class Game{


    protected:

    Board board;
    bool gameOver;
    Apple apple[10]; //there are 10 apples on the screen, when one is eaten it respawns in another point

    public:

    Game(int height, int width);

    //Board getter

    int getHeight();

    int getWidth();

    //Board logic

    void processInput();

    void updateState();

    void redraw();

    bool isOver();


    //Apple methods

    Position randomPosition(){
        srand(time(0));
        Position p;
        //p.x = rand()% // maxX ??
        return p;
    }

    void printApple(int x, int y);

    void removeApple(int x, int y);

    //Snake methods

    // x, y are the coordinates of the snake's tail
    // z, w are the coordinates of the snake's head
    void printSnake(int x, int y, int z, int w);




};



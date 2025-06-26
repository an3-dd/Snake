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

    Position randomPosition();

    void printApple(Position p);

    void removeApple(Position p);
    

    //Snake methods

    // t is the position of the tail, h for the head
    void printSnake(Position t, Position h);




};



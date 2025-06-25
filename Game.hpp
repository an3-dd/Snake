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

    //print an apple in the game's board
    void printApple(int x, int y);

    // remove an apple from the game's board
    void removeApple(int x, int y);

    // print a snake in the game's board
    // x, y are the coordinates of the snake's tail
    // z, w are the coordinates of the snake's head
    void printSnake(int x, int y, int z, int w);

    



};



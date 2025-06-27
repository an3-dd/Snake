//#pragma once 

#include <ncurses.h>
#include "Position.hpp"
#include "Const.hpp"

class Snake{


    protected:

    bool body[WIDTH][HEIGHT]; //snake is a boolean matrix, length is in Const.hpp file
    Position headPosition;
    Position tailPosition;
    char headIcon;
    char bodyIcon;


    public:

    Snake();

    // return the head's coordinate
    Position getHead();

    // return the tail's coordinate
    Position getTail();

    char getHeadIcon();

    char getBodyIcon();

    // allow the snake to move
    void move();

    // allow the snake to move up
    void moveUp();

    // allow the snake to move down
    void moveDown();

    // allow the snake to move left
    void moveLeft();

    // allow the snake to move right
    void moveRight();


};
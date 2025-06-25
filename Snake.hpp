#pragma once 

#include <ncurses.h>


class Snake{


    protected:

    bool body[1][1];
    char headIcon;
    char bodyIcon;


    public:

    Snake();

    // return the tail's coordinate
    bool getTail();

    // return the head's coordinate
    bool getHead();

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
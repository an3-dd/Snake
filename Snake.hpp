//#pragma once 

#include <ncurses.h>
#include "Position.hpp"
#include "Const.hpp"

enum Direction {NONE, UP, DOWN, LEFT, RIGHT};

class Snake{


    protected:

    //snake is a boolean matrix, length is in Const.hpp file
    bool body[WIDTH][HEIGHT]; 
    Position headPosition;
    Position tailPosition;
    Direction currentDirection;

    //to update the tail position, i store the previous directions
    //so i know in which direction the head has moved (length) steps before
    Direction dirHistory[SNAKE_LENGTH]; 
    int indexCircular; //for the circular array logic

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

    // allow the snake to move, it returns the old tail position
    Position move(Direction inputDirection);

};
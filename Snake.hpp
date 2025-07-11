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

    //for the circular array logic
    int indexCircular; 

    char headIcon;
    char bodyIcon;


    public:

    Snake();

    Position getHead();

    Position getTail();

    char getHeadIcon();

    char getBodyIcon();

    // allow the snake to move, it returns false if it collides with himself
    bool move(Direction inputDirection);

    // returns true if the snake is in position p
    bool snakeIsHere(Position p);

    // it's the same as the constructor, but it resets the snake
    void reset();

};
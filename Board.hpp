#pragma once

#include <ncurses.h>
#include "Position.hpp"

class Board{

    protected:

    WINDOW *win;

    int win_x; // x coordinate of the window
    int win_y; // y coordinate of the window
    
    public:

    Board();

    // return the board's window
    WINDOW *getWin();

    // initialize the board
    void init();

    // add the boarder to the board
    void addBorder();

    // refresh the board's content
    void refreshW();

    // delete the board's content
    void clear();

    // add a char in a point
    void addCharAt(Position pos, chtype ch);

    void addCharAt(int x, int y, chtype ch);

    // add an array of char in position pos
    void addStringAt(Position pos, char str[]);

    void addStringAt(int x, int y, char str[]);

    // return the button's code of a pressed button
    int getInput();

    // returns the char at x, y
    char getCharAt(Position pos);

    // remove the char at x, y
    void rmCharAt(Position pos);

    // return true if the x, y, dot is empty
    bool isEmpty(Position pos);

};
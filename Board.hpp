#pragma once

#include <ncurses.h>
#include "Position.hpp"

class Board{

    protected:

    WINDOW *win;

    // coordinates of top-left corner of the window
    int win_x;
    int win_y;
    
    public:

    Board();
    ~Board();

    // return the board's window
    WINDOW *getWin();

    // initialize the board
    void init();

    // add the boarder to the board
    void addBorder();

    // delete the board's content
    void clear();

    // add a char in a position
    void addCharAt(Position pos, chtype ch);

    // add a char in a position with a color pair
    void addCharAt(Position pos, chtype ch, int colorPair);

    // add an array of char in position pos
    void addStringAt(Position pos, char str[]);

    // return the button's code of a pressed button
    int getInput();

    // returns the char at position pos
    char getCharAt(Position pos);

    // remove the char at position pos
    void rmCharAt(Position pos);

    // return true if there is no char at position pos
    bool isEmpty(Position pos);

};
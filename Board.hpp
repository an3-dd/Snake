#include <ncurses.h>
#include "Position.hpp"
#include "Const.hpp"

class Board{

    protected:

    WINDOW *win;
    int height = HEIGHT;
    int width = WIDTH;



    public:

    Board(int height, int width);

    int getWidth();

    int getHeigth();

    // initialize the board
    void init();

    // add the boarder to the board
    void addBorder();

    // refresh the board's content
    void refresh();

    // delete the board's content
    void clear();

    // add a char in a point
    //WAS void addCharAt(int y, int x, chtype ch);
    void addCharAt(Position pos, chtype ch);

    // return the button's code of a pressed button
    int getInput();

    // returns the char at x, y
    //WAS char getCharAt(int x, int y);
    char getCharAt(Position pos);

    // remove the char at x, y
    //WAS void rmCharAt(int x, int y);
    void rmCharAt(Position pos);

    // return true if the x, y, dot is empty
    //WAS bool isEmpty(int x, int y);
    bool isEmpty(Position pos);
    
};
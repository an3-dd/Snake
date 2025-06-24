#include <ncurses.h>


class Board{

    protected:

    WINDOW *win;
    int height = 0;
    int width = 0;



    public:

    Board(int height, int width);

    // return the board's heigth
    int getHeight();

    // return the board's width
    int getWidth();

    // initialize the board
    void init();

    // add the boarder to the board
    void addBorder();

    // refresh the board's content
    void refresh();

    // delete the board's content
    void clear();

    // add a char in a point
    void addCharAt(int y, int x, chtype ch);

    // return the button's code of a pressed button
    int getInput();

    // returns the char at x, y
    char getCharAt(int x, int y);

    // remove the char at x, y
    void rmCharAt(int x, int y);

    // return true if the x, y, dot is empty
    bool isEmpty(int x, int y){
        return mvwinch(win, y, x) == ' ';
    }



};
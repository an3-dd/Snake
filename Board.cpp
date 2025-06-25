
#include "Board.hpp"
#include <ncurses.h>

Board::Board(int height, int width){


    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);


    // create a window in the center of the terminal
    this->win = newwin(height, width, (maxY / 2) - (height / 2), (maxX / 2) - (width / 2));

    init();
    
    this->height = height;
    this->width = width;
}

int Board::getHeight(){
    return this->height;
}

int Board::getWidth(){
    return this->width;
}

void Board::init(){
    clear();
    refresh();
}

void Board::addBorder(){
    box(win, 0, 0);
}

void Board::clear(){
    wclear(win);
    addBorder();
}

void Board::refresh(){
    wrefresh(win);
}

void Board::addCharAt(Position p, chtype ch){
    mvwaddch(win, p.y, p.x, ch);
    wrefresh(win);
}

int Board::getInput(){
    return wgetch(win);
}

char Board::getCharAt(Position p){
    chtype ch = mvinch(p.y, p.x);
    char c = ch & A_CHARTEXT;

    return c;
}

void Board::rmCharAt(Position p){
    mvwaddch(win, p.y, p.x, ' ');
}

bool Board::isEmpty(Position p){
    return mvwinch(win, p.y, p.x) == ' ';
}



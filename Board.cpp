
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

void Board::addCharAt(int x, int y, chtype ch){
    mvwaddch(win, y, x, ch);
    wrefresh(win);
}

int Board::getInput(){
    return wgetch(win);
}

char Board::getCharAt(int x, int y){
    chtype ch = mvinch(y, x);
    char c = ch & A_CHARTEXT;

    return c;
}

void Board::rmCharAt(int x, int y){
    mvwaddch(win, y, x, ' ');
}

void Board::printApple(int x, int y){
    if (isEmpty(x, y)) addCharAt(x, y, this->apple.getIcon());
}

void Game::removeApple(int x, int y){
    if (board.getCharAt(x, y) == apple.getIcon()){
        board.rmCharAt(x, y);
    }
}



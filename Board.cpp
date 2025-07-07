//#pragma once  //da warning

#include "Board.hpp"
#include "Const.hpp"
#include <ncurses.h>

Board::Board(){

    initscr();

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    win_y = (maxY / 2) - (HEIGHT / 2);
    win_x = (maxX / 2) - (WIDTH / 2);


    // create a window in the center of the terminal
    this->win = newwin(HEIGHT, WIDTH, win_y, win_x);

    init();
}

void Board::init(){
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();
    refresh();
}

WINDOW *Board::getWin(){
    return this->win;
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

void Board::addStringAt(Position p, char str[]){

    int i = 0;

    while (str[i] != '\0'){
        addCharAt(p, str[i]);
        p.x++;
        i++;
    }
}

int Board::getInput(){
    return wgetch(win);
}

char Board::getCharAt(Position p){
    chtype ch = mvwinch(win, p.y, p.x);
    return ch & A_CHARTEXT;
}

void Board::rmCharAt(Position p){
    mvwaddch(win, p.y, p.x, ' ');
    wrefresh(win);
}

bool Board::isEmpty(Position p){
    return mvwinch(win, p.y, p.x) == ' ';
}

void Board::printScore(int score) {
    int x = win_x + WIDTH / 2 - 7; // Centered above the window
    int y = win_y - 1; // One line above the window
    mvprintw(y, x, "Score: %d", score);
    refresh();
}

void Board::clearScore() {
    int x = win_x + WIDTH / 2 - 7;
    int y = win_y - 1;
    mvprintw(y, x, "                  ");//l'implementazione non funziona, ma non so perche
    refresh();
}



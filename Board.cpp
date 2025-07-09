#include "Board.hpp"
#include "Const.hpp"
#include <ncurses.h>

Board::Board() {

  initscr();

  int maxY, maxX;
  getmaxyx(stdscr, maxY, maxX);
  win_y = (maxY / 2) - (HEIGHT / 2);
  win_x = (maxX / 2) - (WIDTH / 2);

  // create a window in the center of the terminal
  this->win = newwin(HEIGHT, WIDTH, win_y, win_x);

  init();
}

Board::~Board() {
    if (win) delwin(win);
}

void Board::init(){
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    clear();
    refresh();

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);   // Apple color
        init_pair(2, COLOR_GREEN, COLOR_BLACK); // Snake color
    }
}

WINDOW *Board::getWin() { return this->win; }

void Board::addBorder() { box(win, 0, 0); }

void Board::clear() {
  wclear(win);
  addBorder();
}

void Board::addCharAt(int x, int y, chtype ch) {
  mvwaddch(win, y, x, ch);
  wrefresh(win);
}

void Board::addCharAt(Position p, chtype ch) {
  mvwaddch(win, p.y, p.x, ch);
  wrefresh(win);
}

void Board::addCharAt(Position pos, chtype ch, int colorPair) {
    wattron(win, COLOR_PAIR(colorPair));
    mvwaddch(win, pos.y, pos.x, ch);
    wattroff(win, COLOR_PAIR(colorPair));
    wrefresh(win);
}

void Board::addStringAt(Position p, char str[]) {

  int i = 0;

  while (str[i] != '\0') {
    addCharAt(p, str[i]);
    p.x++;
    i++;
  }
}

void Board::addStringAt(int x, int y, char str[]) {

  int i = 0;

  while (str[i] != '\0') {
    addCharAt(x, y, str[i]);
    x++;
    i++;
  }
}

int Board::getInput() { return wgetch(win); }

char Board::getCharAt(Position p) {
  chtype ch = mvwinch(win, p.y, p.x);
  return ch & A_CHARTEXT;
}

void Board::rmCharAt(Position p) {
  mvwaddch(win, p.y, p.x, ' ');
  wrefresh(win);
}

bool Board::isEmpty(Position p) { return mvwinch(win, p.y, p.x) == ' '; }




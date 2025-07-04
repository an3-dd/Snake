#include <ncurses.h>
#include "Game.hpp"
// #include <cstring>


int main(int argc, char ** argv){

    // initscr();
    // refresh();
    // noecho();
    // curs_set(0);

    Game game;

    game.openMenu();

    cout << game.getMenu().getCurrentLevel().name;



    return 0;
}
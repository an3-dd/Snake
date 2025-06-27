#include <ncurses.h>
#include "Position.hpp"
#include "Const.hpp"
#include "Game.hpp"


int main(int argc, char ** argv){


    initscr();
    refresh();
    noecho();
    curs_set(0);

    Game game;

    char c;

    game.initPrintSnake();

    while(c != 'q'){



        c = getch();


        // if press 'a' button print an apple in random position
        if (c == 'a'){
            Position p = game.randomPosition();
            game.printApple(p);
        }

        refresh();
    }


    endwin();



    return 0;
}
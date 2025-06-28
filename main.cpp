#include <ncurses.h>
#include "Position.hpp"
#include "Game.hpp"
#include <cstring>


int main(int argc, char ** argv){


    initscr();
    refresh();
    noecho();
    curs_set(0);

    Game game;

    char c;

    // game.initPrintSnake();

    while(c != 'q'){



        c = getch();


        // if press 'a' button print an apple in random position
        if (c == 'a'){
            Position p = game.randomPosition();
            game.printApple(p);
        }
        else if (c == 'b'){

            char ciao[10];
            strcpy(ciao, "ciao");
            Position a = game.randomPosition();
            game.getBoard().addStringAt(a, ciao);

        }

        refresh();
    }


    endwin();



    return 0;
}
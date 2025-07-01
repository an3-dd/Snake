#include <ncurses.h>
#include "Position.hpp"
#include "Game.hpp"
#include <cstring>


int main(int argc, char ** argv){

    // initscr();
    // refresh();
    // noecho();
    // curs_set(0);

    Game game;

    char c;

    // game.initPrintSnake();

    game.openMenu();

/*
    while(c != 'q'){

        c = getch();
        switch (c) {




            //movement
            case 'w': game.updateSnake(UP); break;
            case 's': game.updateSnake(DOWN); break;
            case 'a': game.updateSnake(LEFT); break;
            case 'd': game.updateSnake(RIGHT); break;

            //DEBUG print apple in random position
            case 'k': {
                Position p = game.randomPosition();
                game.printApple(p); break;
            }

             //DEBUG print string
             case 'b': {
                 char ciao[10];
                 strcpy(ciao, "ciao");
                 Position a = game.randomPosition();
                 game.getBoard().addStringAt(a, ciao); break;
             }
             //open menu
             case 'm': game.openMenu(); break;

            default: break;

        }
        refresh();
    }

    endwin();
*/
    return 0;
}
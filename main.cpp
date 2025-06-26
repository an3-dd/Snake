#include <ncurses.h>
#include "Game.hpp"


int main(int argc, char ** argv){


    initscr();
    refresh();
    noecho();

    Game game(50, 150);

    char c;

    while(c != 'q'){



        c = getch();


        // if press 'a' button print an apple in random position
        if (c == 'a'){
            Position p = game.randomPosition();
            game.printApple(p);
        }
    }


    endwin();



    return 0;
}
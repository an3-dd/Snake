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


        // if press 'a' button print an apple in the x, y position
        if (c == 'a'){
            game.printApple(5, 10);
        }
    }


    endwin();



    return 0;
}
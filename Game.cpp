#include "Game.hpp"
#include "Menu.hpp"
#include "Position.hpp"
#include <iostream>
#include <ncurses.h>
#include <cstring>
using namespace std;

// inutile perche il costruttor inzializza
// automaticamente tutti gli oggetti al suo interno
// Game::Game(): board(), menu(){
// questo serve solo quando vogliamo usare un cstruttore
// diverso da quello di default

Game::Game(){
    srand(time(0));
    center.x = WIDTH/2;
    center.y = HEIGHT/2;
    gameState = onMenu;
    for(int i = 0; i < 10; i++){
        apple[i] = Apple(randomPosition());
    }
}

//LOGIC

Position Game::randomPosition(){
    Position p;
    p.x = rand() % WIDTH;
    p.y = rand() % HEIGHT;
    return p;
}

void Game::processInput(){

    int scelta = menu.getChoice();

    switch (scelta) {

        case 0: startGame(); break;
        case 1: scriba.showScores(); openMenu(); break;
        case 2: menu.showLevels(); openMenu(); break;
        case 3: exitGame(); break;
        default : break;
    }
    menu.resetChoice();
}


//SCREENS

void Game::openMenu(){
    gameState = onMenu;
    menu.open();
    processInput();
}


void Game::openDeathScreen(){
    gameState = onDeathScreen;
    //todo (look at score, quit game...)
    openMenu();
}


// void processLevel();

void Game::exitGame(){
    flushinp();
    endwin();
    exit(0);
}


void Game::startGame(){

    gameState = onGame;

    board.init();

    board.addBorder();

    board.refresh();
    initPrintSnake();

    char c;
    while (gameState == onGame && c != 'q'){
        c = getch();
        switch (c) {

            //movement
            case 'w': updateSnake(UP); break;
            case 's': updateSnake(DOWN); break;
            case 'a': updateSnake(LEFT); break;
            case 'd': updateSnake(RIGHT); break;
            
            //DEBUG print apple in random position
            case 'k': {
                Position p = randomPosition();
                printApple(p); break;
            }

            //DEBUG print string
            case 'b': {
                char ciao[10];
                strcpy(ciao, "ciao");
                Position a = randomPosition();
                getBoard().addStringAt(a, ciao); break;
            }
            //open menu
            case 'm': {
                gameState = onMenu; //forse non serve
                openMenu(); break;
            }

            default: break;

        }
        board.refresh();
    }

    endwin();
    exit(0);

}



//GETTER METHODS

Scriba Game::getScriba(){
    return scriba;
}

Menu Game::getMenu(){
    return this->menu;
}

Board Game::getBoard(){
    return this->board;
}

GameState Game::getGameState(){
    return gameState;
}



//APPLE METHODS

void Game::printApple(Position p){
    if (board.isEmpty(p)) board.addCharAt(p, this->apple[0].getIcon()); //the apple index doesn't matter
}

void Game::removeApple(Position p){
    if (board.getCharAt(p) == this->apple[0].getIcon()){
        board.rmCharAt(p);
    }
}



//SNAKE METHODS

void Game::initPrintSnake(){ //only called at the start
    //add head
    board.addCharAt(center, this->snake.getHeadIcon());

    //add body
    //delta is the position where to spawn the next segment
    Position delta = center; 
    for(int i=1; i<SNAKE_LENGTH; i++){
        delta.y = center.y+i;
        board.addCharAt(delta, this->snake.getBodyIcon());
    }

    board.refresh();
}

void Game::updateSnake(Direction inputDirection) {
    ///store the head position before movement
    Position previousHead = snake.getHead();

    //remove tail
    board.rmCharAt(snake.getTail());

    if(!snake.move(inputDirection)) openDeathScreen();

    board.refresh(); //to force another refresh

    //draw body icon where the head was
    board.addCharAt(previousHead, snake.getBodyIcon());

    //draw new head
    board.addCharAt(snake.getHead(), snake.getHeadIcon());
}

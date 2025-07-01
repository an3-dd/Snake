#include "Game.hpp"
#include "Menu.hpp"
#include "Position.hpp"
#include <iostream>
#include <ncurses.h>
#include <cstring>
using namespace std;

Game::Game(): board(), menu(){
    srand(time(0));
    board.init();
    this->openMenu();
    center.x = WIDTH/2;
    center.y = HEIGHT/2;
    this->gameOver = false;
    for(int i=0; i<10; i++){
        apple[i] = Apple(randomPosition());
    }
}

void Game::openMenu(){
    menu.open();
    processInput();
}

void Game::processInput(){

    switch (menu.getChoice()) {

        case 0: startGame(); break;
        case 1: /*scriba.showScores();*/ break;
        case 2: 
        menu.showLevels(); break;
        case 3: exitGame(); break;
        default : break;
    
    }
}

// void processLevel();


// non funziona
void Game::exitGame(){
    if (menu.getChoice() == 3) {
        refresh();
        endwin();
    }
}


void Game::startGame(){

    board.init();
    
    board.refresh();

    initPrintSnake();

    char c;
    while (c != 'q'){
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
             case 'm': openMenu(); break;

            default: break;

        }
        refresh();
    }

    endwin();

}


Menu Game::getMenu(){
    return this->menu;
}



Board Game::getBoard(){
    return this->board;
}

bool Game::isOver(){
    return gameOver;
}

void Game::updateState(){
    //updateSnake();
    //TODO
}

Position Game::randomPosition(){
    Position p;
    p.x = rand() % WIDTH;
    p.y = rand() % HEIGHT;
    return p;
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
}

void Game::updateSnake(Direction inputDirection){
    
    //store the head position before movement
    Position previousHead = snake.getHead();

    Position oldTail = snake.move(inputDirection);

    char buf[100];
    sprintf(buf, "PrevHead:(%d,%d) OldTail:(%d,%d) Head:(%d,%d)\n",
        previousHead.x, previousHead.y,
        oldTail.x, oldTail.y,
        snake.getHead().x, snake.getHead().y);
    std::cerr << buf;

    //remove tail
    board.rmCharAt(oldTail);

    //draw body icon where the head was
    board.addCharAt(previousHead, snake.getBodyIcon());

    //draw new head
    board.addCharAt(snake.getHead(), snake.getHeadIcon());

}


#include "Game.hpp"


Game::Game(): board(){
    srand(time(0));
    board.init();
    center.x = WIDTH/2;
    center.y = HEIGHT/2;
    this->gameOver = false;
    for(int i=0; i<10; i++){
        apple[i] = Apple(randomPosition());
    }
}



bool Game::isOver(){
    return gameOver;
}

void Game::updateState(){
    //TODO
}

Position Game::randomPosition(){
    Position p;
    p.x = rand() % WIDTH;
    p.y = rand() % HEIGHT;
    return p;
}


void Game::printApple(Position p){
    if (board.isEmpty(p)) board.addCharAt(p, this->apple[0].getIcon()); //the apple index doesn't matter
}

void Game::removeApple(Position p){
    if (board.getCharAt(p) == this->apple[0].getIcon()){
        board.rmCharAt(p);
    }
}

void Game::initPrintSnake(){ //only called at the start
    //add head
    board.addCharAt(center, this->snake.getHeadIcon());

    //add body
    Position delta = center; //delta is the position where to spawn the next segment
    for(int i=1; i<SNAKE_LENGTH; i++){
        delta.y = center.y+i;
        board.addCharAt(delta, this->snake.getBodyIcon());
    }
}


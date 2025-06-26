#include "Game.hpp"


Game::Game(int height, int width): board(height, width){ //WAS , apple(0,0)
    srand(time(0));
    board.init();
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


//void Game::printSnake(int x, int y){
//    
//}



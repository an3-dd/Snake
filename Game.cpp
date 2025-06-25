#include "Game.hpp"


Game::Game(int height, int width): board(height, width){ //WAS , apple(0,0)
    board.init();
    this->gameOver = false;
    for(int i=0; i<10; i++){
        apple[i] = Apple(randomPosition());
    }
} //TODO


int Game::getHeight(){
    return this->board.getHeight();
}

int Game::getWidth(){
    return this->board.getWidth();
}

bool Game::isOver(){
    return gameOver;
}

void Game::updateState(){
    
}

/*
void Game::printApple(int x, int y){
    if (board.isEmpty(x, y)) board.addCharAt(x, y, this->apple.getIcon());
}

void Game::removeApple(int x, int y){
    if (board.getCharAt(x, y) == apple.getIcon()){
        board.rmCharAt(x, y);
    }
}*/


//void Game::printSnake(int x, int y){
//    
//}



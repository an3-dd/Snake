
#include "Game.hpp"


Game::Game(int height, int width): board(height, width){
    board.init();
    this->gameOver = false;
}


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


//void Game::printSnake(int x, int y){
//    
//}



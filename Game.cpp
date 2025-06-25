
#include "Game.hpp"


Game::Game(int height, int width): board(height, width) , apple(0, 0){
    board.init();
    this->gameOver = false;
}


int Game::getHeight(){
    return this->board.getHeight();
}

int Game::getWidth(){
    return this->board.getWidth();
}

void Game::redraw(){
    board.refresh();
}

bool Game::isOver(){
    return gameOver;
}

void Game::updateState(){
    
}


void Game::printApple(int x, int y){
    if (board.isEmpty(x, y)) board.addCharAt(x, y, this->apple.getIcon());
}

void Game::removeApple(int x, int y){
    if (board.getCharAt(x, y) == apple.getIcon()){
        board.rmCharAt(x, y);
    }
}

//void Game::printSnake(int x, int y){
//    
//}



#include "Snake.hpp"

Snake::Snake(){
    for (int x=0; x<WIDTH; x++){ //initialization
        for (int y=0; y<HEIGHT; y++){
            body[x][y] = false;
        }
    }
    
    //the snake is initialized vertically from the center (head)
    int centerX = WIDTH/2;
    int centerY = HEIGHT/2;
    for(int i=0; i<SNAKE_LENGTH; i++){
        body[centerX][centerY-i] = true;
    }
    headPosition = Position(centerX, centerY);
    tailPosition = Position(centerX, centerY+1-SNAKE_LENGTH);

    headIcon = '@';
    bodyIcon = 'o';
} 

Position Snake::getHead(){
    return headPosition;
}

Position Snake::getTail(){
    return tailPosition;
}

char Snake::getHeadIcon(){
    return headIcon;
}

char Snake::getBodyIcon(){
    return bodyIcon;
}


#include "Snake.hpp"
#include <iostream>
using namespace std;

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
        body[centerX][centerY+i] = true;
    }
    headPosition = Position(centerX, centerY); 
    tailPosition = Position(centerX, centerY-1+SNAKE_LENGTH); //(0,0) in upper-left angle

    currentDirection = NONE;
    indexCircular = 0;
    for(int i=0; i<SNAKE_LENGTH; i++){
        dirHistory[i] = UP; //this is because the snake is initialized vertically
    }

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

bool Snake::snakeIsHere(Position p){
    return body[p.x][p.y];
}

bool Snake::move(Direction inputDirection) {

    //we first check if the direction is valid, we set it to none if not valid
    switch (inputDirection) {
        case UP:{
            if(currentDirection == DOWN) inputDirection = NONE; break;
        }
        case DOWN:{
            if(currentDirection == UP) inputDirection = NONE; break;
        }
        case LEFT:{
            if(currentDirection == RIGHT) inputDirection = NONE; break;
        }
        case RIGHT:{
            if(currentDirection == LEFT) inputDirection = NONE; break;
        }
        default: break;
    }
    //if there is a valid input direction, change the current direction to that
    if (inputDirection != NONE) currentDirection = inputDirection;

    //set tailDirection as the direction the head had a cycle before
    Direction tailDirection = dirHistory[(indexCircular + 1) % SNAKE_LENGTH]; //LA CODA FUNZIONA CON +1
    
    //save the current direction in history
    dirHistory[indexCircular] = currentDirection;

    //calculate new head position
    Position newHead = headPosition;
    switch (currentDirection) { //the module is to account for "pacman effect"
        case UP: newHead.y = (newHead.y - 1 + HEIGHT) % HEIGHT; break;
        case DOWN: newHead.y = (newHead.y + 1) % HEIGHT; break;
        case LEFT: newHead.x = (newHead.x - 1 + WIDTH) % WIDTH; break;
        case RIGHT: newHead.x = (newHead.x + 1) % WIDTH; break;
        default: break;
    }

    //check if it collides with himself, if it does, return false
    if(snakeIsHere(newHead)) return false;

    //update the head
    body[newHead.x][newHead.y] = true;
    headPosition = newHead;

    // Clear old tail position and update tailPosition accordingly
    body[tailPosition.x][tailPosition.y] = false;
    switch (tailDirection) {
        case UP:    tailPosition.y = (tailPosition.y - 1 + HEIGHT) % HEIGHT; break;
        case DOWN:  tailPosition.y = (tailPosition.y + 1) % HEIGHT; break;
        case LEFT:  tailPosition.x = (tailPosition.x - 1 + WIDTH) % WIDTH; break;
        case RIGHT: tailPosition.x = (tailPosition.x + 1) % WIDTH; break;
        default: break;
    }

    //increment the index for the next movement
    indexCircular = (indexCircular + 1) % SNAKE_LENGTH;

    //movement was succesful
    return true;

}



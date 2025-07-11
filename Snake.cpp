#include "Snake.hpp"

Snake::Snake() {
  // initialization of the matrix
  for (int x = 0; x < WIDTH; x++) { 
    for (int y = 0; y < HEIGHT; y++) {
      body[x][y] = false;
    }
  }

  // the snake is initialized vertically from the center (head)
  int centerX = WIDTH / 2;
  int centerY = HEIGHT / 2;
  for (int i = 0; i < SNAKE_LENGTH; i++) {
    body[centerX][centerY + i] = true;
  }
  headPosition = Position(centerX, centerY);
  tailPosition = Position(centerX, centerY - 1 + SNAKE_LENGTH); //(0,0) in upper-left angle

  currentDirection = UP;
  indexCircular = 0;
  for (int i = 0; i < SNAKE_LENGTH; i++) {
    dirHistory[i] = UP; // this is because the snake is initialized vertically
  }

  headIcon = '@';
  bodyIcon = 'o';
}

Position Snake::getHead() { return headPosition; }

Position Snake::getTail() { return tailPosition; }

char Snake::getHeadIcon() { return headIcon; }

char Snake::getBodyIcon() { return bodyIcon; }

bool Snake::snakeIsHere(Position p) { return body[p.x][p.y]; }

bool Snake::move(Direction inputDirection) {

  // we first check if the direction is valid, we set it to none if not valid

  if (inputDirection == UP) {
    if (currentDirection == DOWN) inputDirection = NONE;
  } 
  else if (inputDirection == DOWN) {
    if (currentDirection == UP) inputDirection = NONE;
  } 
  else if (inputDirection == LEFT) {
    if (currentDirection == RIGHT) inputDirection = NONE;
  } 
  else if (inputDirection == RIGHT) {
    if (currentDirection == LEFT) inputDirection = NONE;
  }

  // if there is a valid input direction, change the current direction to that
  if (inputDirection != NONE)
    currentDirection = inputDirection;

  // set tailDirection as the direction the head had a cycle before
  Direction tailDirection =
      dirHistory[(indexCircular + 1) % SNAKE_LENGTH]; // LA CODA FUNZIONA CON +1

  // save the current direction in history
  dirHistory[indexCircular] = currentDirection;

  // calculate new head position
  Position newHead = headPosition;

  // loop one step before the border
  if (currentDirection == UP) {
    if (newHead.y == 1) newHead.y = HEIGHT - 2;
    else newHead.y = newHead.y - 1;
  } 
  else if (currentDirection == DOWN) {
    if (newHead.y == HEIGHT - 2) newHead.y = 1;
    else newHead.y = newHead.y + 1;
  } 
  else if (currentDirection == LEFT) {
    if (newHead.x == 1) newHead.x = WIDTH - 2;
    else newHead.x = newHead.x - 1;
  } 
  else if (currentDirection == RIGHT) {
    if (newHead.x == WIDTH - 2) newHead.x = 1;
    else newHead.x = newHead.x + 1;
  }

  // check if it collides with himself, if it does, return false
  if (snakeIsHere(newHead))
    return false;

  // update the head
  body[newHead.x][newHead.y] = true;
  headPosition = newHead;

  // clear old tail position and update tailPosition accordingly
  body[tailPosition.x][tailPosition.y] = false;

  if (tailDirection == UP) {
    if (tailPosition.y == 1) tailPosition.y = HEIGHT - 2;
    else tailPosition.y = tailPosition.y - 1;
  }
  else if (tailDirection == DOWN) {
    if (tailPosition.y == HEIGHT - 2) tailPosition.y = 1;
    else tailPosition.y = tailPosition.y + 1;
  }
  else if (tailDirection == LEFT) {
    if (tailPosition.x == 1) tailPosition.x = WIDTH - 2;
    else tailPosition.x = tailPosition.x - 1;
  }
  else if (tailDirection == RIGHT) {
    if (tailPosition.x == WIDTH - 2) tailPosition.x = 1;
    else tailPosition.x = tailPosition.x + 1;
  }


  // increment the index for the next movement
  indexCircular = (indexCircular + 1) % SNAKE_LENGTH;

  // movement was succesful
  return true;
}

void Snake::reset() {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      body[x][y] = false;
    }
  }
  int centerX = WIDTH / 2;
  int centerY = HEIGHT / 2;
  for (int i = 0; i < SNAKE_LENGTH; i++) {
    body[centerX][centerY + i] = true;
  }
  headPosition = Position(centerX, centerY);
  tailPosition = Position(centerX, centerY - 1 + SNAKE_LENGTH);
  currentDirection = UP;
  indexCircular = 0;
  for (int i = 0; i < SNAKE_LENGTH; i++) {
    dirHistory[i] = UP;
  }
}

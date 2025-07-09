#include "Game.hpp"
#include "Const.hpp"
#include "Menu.hpp"
#include "Position.hpp"
#include <ncurses.h>

using namespace std;


Game::Game(){
    srand(time(0));
    
    center.x = WIDTH/2;
    center.y = HEIGHT/2;
    gameState = onMenu;
    for(int i = 0; i < APPLE_COUNT; i++){
        apple[i] = Apple();
    }

    score = 0;
    currentDirection = UP; // Default starting direction

    openMenu();
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
    if (scelta == 0) startGame();
    else if (scelta == 1){
        scriba.showScores();
        openMenu();
    }
    else if (scelta == 2){
        menu.showLevels();
        openMenu();
    }
    else if (scelta == 3){
        exitGame();
    }
    menu.resetChoice();
}


void Game::processInputDeath(){

    int scelta = menu.getChoice();
    if (scelta == 0) openMenu();
    else if (scelta == 1) exitGame();
    menu.resetChoice();
}


//SCREENS

void Game::printScore() {

    char buffer[10];
    sprintf(buffer, "%d", score);

    char score[] = {"Score: "};
    board.addStringAt(0, 0, score);
    board.addStringAt(7, 0, buffer);
    refresh();
}


void Game::printTimer() {
    int elapsedPause = 0;
    if (gameState == onMenu && pauseTime > 0) {
        elapsedPause = (int)(pauseTime - startTime);
    } else {
        elapsedPause = (int)(time(nullptr) - startTime);
    }
    int secondsLeft = timeLimit - elapsedPause;
    if (secondsLeft < 0) secondsLeft = 0;
    int min = secondsLeft / 60;
    int sec = secondsLeft % 60;
    char buffer[16];
    sprintf(buffer, "%02d:%02d", min, sec);

    char timer[] = {"Timer: "};
    board.addStringAt(WIDTH - 12, 0, timer);
    board.addStringAt(WIDTH - 5, 0, buffer);
    refresh();
}



void Game::openMenu(){
    // Pause the timer
    if (gameState == onGame) {
        pauseTime = time(nullptr);
    }
    gameState = onMenu;
    menu.open();
    processInput();
}

void Game::startGame(){
    gameState = onGame;

    board.init();
    snake.reset();

    board.addBorder();
    refresh();

    initPrintSnake();
    refresh();

    spawnApples();
    refresh();

    printScore();
    refresh();

    // TIMER SETUP
    if (pauseTime > 0) {
        // Resume timer
        startTime += (time(nullptr) - pauseTime);
    } else {
        startTime = time(nullptr);
    }
    pauseTime = 0;
    printTimer();
    refresh();

    char tornamenu[] = {"PRESS M TO MENU"};
    board.addStringAt(center.x - 7, HEIGHT-1, tornamenu);
    refresh();


    int baseDelay = 200;
    int speedMult = 1;
    int scelta = menu.getCurrentLevel().diff;

    if (scelta == 0) speedMult = menu.getCurrentLevel().diff+1;
    else if (scelta == 1) speedMult = menu.getCurrentLevel().diff+2;
    else if (scelta == 2) speedMult = menu.getCurrentLevel().diff+3;

    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    int c = 0;

    while (gameState == onGame){
        c = getch();
        if (c == 'w' || c == 'W' || c == KEY_UP){
            currentDirection = UP;
        }
        else if (c == 's' || c == 'S' || c == KEY_DOWN){
            currentDirection = DOWN;
        }
        else if (c == 'a' || c == 'A' || c == KEY_LEFT){
            currentDirection = LEFT;
        }
        else if (c == 'd' || c == 'D' || c == KEY_RIGHT){
            currentDirection = RIGHT;
        }
        else if (c == 'm' || c == 'M'){
            openMenu();
        }

        updateSnake(currentDirection);
        // TIMER UPDATE (freeze if paused)
        int elapsed;
        if (gameState == onMenu && pauseTime > 0) {
            elapsed = (int)(pauseTime - startTime);
        } 
        else {
            elapsed = (int)(time(nullptr) - startTime);
        }
        int secondsLeft = timeLimit - elapsed;
        if (secondsLeft < 0) secondsLeft = 0;
        printTimer();
        if (secondsLeft == 0) {
            openDeathMenu();
            break;
        }
        refresh();
        napms(baseDelay / speedMult);
    }

    endwin();
    exit(0);
}



void Game::openDeathMenu(){
    gameState = onDeathScreen;
    int scelta = menu.getCurrentLevel().diff;

    if (scelta == 0) scriba.insert(score+((menu.getCurrentLevel().diff+1)*100), "facile");
    else if (scelta == 1) scriba.insert(score+((menu.getCurrentLevel().diff+1)*100), "medio");
    else if (scelta == 2) scriba.insert(score+((menu.getCurrentLevel().diff+1)*100), "difficile");

    score = 0;
    menu.openDeath();
    processInputDeath();

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

void Game::spawnApples(){
    for(int i=0; i<APPLE_COUNT; i++){
        Position r = randomPosition();
        while (!board.isEmpty(r)) {
            r = randomPosition();
        }
        apple[i] = Apple(r);
        printApple(r);
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

    // board.refresh();
    refresh();
}

void Game::updateSnake(Direction inputDirection) {
    Position previousHead = snake.getHead();
    board.rmCharAt(snake.getTail());

    //check if movement is valid
    if (!snake.move(inputDirection)) {
        openDeathMenu();
        return;
    }

    Position newHead = snake.getHead();

    //Apple check BEFORE placing snake head
    bool ateApple = false;

    int i = 0;
    bool done = false;

    while (i < 10 && !done){
        if (apple[i].getPosition() == newHead) {
            
            //score management
            int scelta = menu.getCurrentLevel().diff;
            if (scelta == 0) score += 1;
            else if (scelta == 1) score += 3;
            else if (scelta == 2) score += 5;

            ateApple = true;

            // remove old apple
            removeApple(apple[i].getPosition());

            // generate a new one
            Position newPos;
            do {
                newPos = randomPosition();
            } while (!board.isEmpty(newPos)); // avoid spawning on the snake

            apple[i] = Apple(newPos);
            printApple(newPos);
            done = true;
        }
        i++;
    }

    //draw body and head
    board.addCharAt(previousHead, snake.getBodyIcon());
    board.addCharAt(snake.getHead(), snake.getHeadIcon());

    //if an apple was eaten, print the score
    if (ateApple) printScore(); 
    
    refresh();
}

void Game::exitGame() {
    endwin();
    exit(0);
}


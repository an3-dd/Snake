#include "Game.hpp"
#include "Menu.hpp"
#include "Position.hpp"
#include <ncurses.h>
#include <cstring>
using namespace std;

Game::Game(){
    srand(time(0));
    score = 0;
    center.x = WIDTH/2;
    center.y = HEIGHT/2;
    gameState = onMenu;
    for(int i = 0; i < APPLE_COUNT; i++){
        apple[i] = Apple();
    }

    score = 0;
    currentDirection = UP; // Default starting direction
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
        switch (scelta) {
            case 0: startGame(); break;
            case 1: scriba.showScores(); openMenu(); break;
            case 2: menu.showLevels(); openMenu(); break;
            case 3: exitGame(); break;
            default: break;
        }
        menu.resetChoice();
}


//SCREENS

void Game::openMenu(){
    board.clearScore(); // Hide the score when entering the menu
    gameState = onMenu;
    menu.setCurrentLevel(0);
    menu.open();
    processInput(); // Revert to calling processInput() here
    
}


void Game::openDeathScreen(){
    gameState = onDeathScreen;
    //todo (look at score, quit game...)
    openMenu();
}



void Game::exitGame(){
    endwin();
    system("clear"); // Clear the terminal after exiting ncurses
    exit(0);
}

void Game::startGame(){

    gameState = onGame;

    board.init();
    board.clear(); // Ensure border is drawn before anything else
    snake.reset(); // Reset snake state

    initPrintSnake();

    spawnApples();

    score = 0;
    board.printScore(score); // Show initial score

    int levelIndex = menu.getLevel();
    int baseDelay = 200; // ms
    int speedMult = 1;
    switch (levelIndex) {
        case 0: speedMult = 1; break; // easy
        case 1: speedMult = 3; break; // medium
        case 2: speedMult = 5; break; // hard
        default: speedMult = 1; break;
    }
    
    nodelay(stdscr, TRUE); // Make getch() non-blocking

    char c = 0;
    while (gameState == onGame && c != 'q'){
        c = getch();
        switch (c) {
            //movement
            case 'w': currentDirection = UP; break;
            case 's': currentDirection = DOWN; break;
            case 'a': currentDirection = LEFT; break;
            case 'd': currentDirection = RIGHT; break;
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
            case 'm': {
                openMenu(); break;
            }

            default: break;

        }
        updateSnake(currentDirection); //automatic movement
        board.refresh();
        napms(baseDelay / speedMult);
    }

    endwin();
    exit(0);

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

    board.refresh();
}

void Game::updateSnake(Direction inputDirection) {
    Position previousHead = snake.getHead();
    board.rmCharAt(snake.getTail());

    //check if movement is valid
    if (!snake.move(inputDirection)) {
        openDeathScreen();
        return;
    }

    Position newHead = snake.getHead();

    //Apple check BEFORE placing snake head
    bool ateApple = false;
    for (int i = 0; i < 10; i++) {
        if (apple[i].getPosition() == newHead) {
            
            //score management
            score += getMenu().getCurrentLevel().bonus;
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
            break;
        }
    }

    //draw body and head
    board.addCharAt(previousHead, snake.getBodyIcon());
    board.addCharAt(snake.getHead(), snake.getHeadIcon());

    //if an apple was eaten, print the score
    if (ateApple) board.printScore(score); 
    
    board.refresh();
}

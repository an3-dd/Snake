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

    // si trova gia in getMenu().getCurrentLevel().bonus
    // ho modificato la funzione in cui questo attributo veniva richiamato
    // bonus = 1;
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
        default : break;
    }
    menu.resetChoice();
}


//SCREENS

void Game::openMenu(){
    gameState = onMenu;
    menu.setCurrentLevel(0);
    menu.open();
    processInput();
}


void Game::openDeathScreen(){
    gameState = onDeathScreen;
    //todo (look at score, quit game...)
    openMenu();
}



void Game::exitGame(){
    endwin();
    exit(0);    // commenta se vuoi stampare sul terminale qualche variabile per verificarne il corretto assegnamento
}


void Game::startGame(){

    gameState = onGame;

    board.init();

    initPrintSnake();

    spawnApples();

    score = 0;

    int levelIndex = menu.getLevel();
    
    //TODO need to get currentLevel with the index

    char c;
    while (gameState == onGame && c != 'q'){
        c = getch();
        switch (c) {

            //movement
            case 'w': updateSnake(UP); break;
            case 's': updateSnake(DOWN); break;
            case 'a': updateSnake(LEFT); break;
            case 'd': updateSnake(RIGHT); break;
            
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
        board.refresh();
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
    for (int i = 0; i < 10; i++) {
        if (apple[i].getPosition() == newHead) {
            
            //score management
            score += getMenu().getCurrentLevel().bonus;

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

    //Draw body and head
    board.addCharAt(previousHead, snake.getBodyIcon());
    board.addCharAt(snake.getHead(), snake.getHeadIcon());

    board.refresh();
}

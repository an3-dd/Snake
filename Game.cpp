#include "Game.hpp"
#include "Const.hpp"
#include "Menu.hpp"
#include "Position.hpp"
#include <ncurses.h>
#include <cstring>
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


void Game::processInputDeath(){

    int scelta = menu.getChoice();
    switch (scelta) {
        case 0: openMenu(); break;
        case 1: exitGame(); break;
        default: break;
    }
    menu.resetChoice();
}


//SCREENS

void Game::printScore() {

    char buffer[10];
    sprintf(buffer, "%d", score);

    board.addStringAt(0, 0, "Score: ");
    board.addStringAt(6, 0, buffer);
    refresh();
}

// non cred che serva realmente
void Game::clearScore() {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    int win_y = (maxY / 2) - (HEIGHT / 2);
    int win_x = (maxX / 2) - (WIDTH / 2);

    int x = win_x + WIDTH / 2 - 7;
    int y = win_y - 1;

    // su quale finestra agisce questa funzione?
    // mvaddnstr(y, x, str, n)
    mvprintw(y, x, "                  ");//l'implementazione non funziona, ma non so perche
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
    board.addStringAt(20, 0, "Timer: ");
    board.addStringAt(27, 0, buffer);
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
    int baseDelay = 200;
    int speedMult = 1;
    switch (menu.getLevel()) {
        case 0: speedMult = 1; break;
        case 1: speedMult = 3; break;
        case 2: speedMult = 5; break;
        default: speedMult = 1; break;
    }
    nodelay(stdscr, TRUE);
    char c = 0;
    while (gameState == onGame && c != 'q'){
        c = getch();
        switch (c) {
            case 'w': currentDirection = UP; break;
            case 's': currentDirection = DOWN; break;
            case 'a': currentDirection = LEFT; break;
            case 'd': currentDirection = RIGHT; break;
            case 'k': {
                Position p = randomPosition();
                printApple(p); break;
            }
            case 'b': {
                char ciao[10];
                strcpy(ciao, "ciao");
                Position a = randomPosition();
                getBoard().addStringAt(a, ciao); break;
            }
            case 'm': {
                openMenu();
                break;
            }
            default: break;
        }
        updateSnake(currentDirection);
        // TIMER UPDATE (freeze if paused)
        int elapsed;
        if (gameState == onMenu && pauseTime > 0) {
            elapsed = (int)(pauseTime - startTime);
        } else {
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
    int scelta = menu.getLevel();
    switch (scelta) {
        case 0: scriba.insert(score, "facile"); break;
        case 1: scriba.insert(score, "medio"); break;
        case 2: scriba.insert(score, "difficile"); break;
        default: break;
    }
    endwin();
    exit(0);
}



void Game::openDeathMenu(){
    gameState = onDeathScreen;
    int scelta = menu.getLevel();
    switch (scelta) {
        case 0: scriba.insert(score, "facile"); break;
        case 1: scriba.insert(score, "medio"); break;
        case 2: scriba.insert(score, "difficile"); break;
        default: break;
    }
    score = 0;
    menu.openDeath();
    mvwprintw(menu.getMenuBoard().getWin(), 0, 0, "HAI FATTO TOT PUNTI");
    wrefresh(menu.getMenuBoard().getWin());
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
    for (int i = 0; i < 10; i++) {
        if (apple[i].getPosition() == newHead) {
            
            //score management
            switch (menu.getLevel()) {
                case 0: score += 1; break; // easy
                case 1: score += 3; break; // medium
                case 2: score += 5; break; // hard
                default: score = 1; break;
            }
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
    if (ateApple) printScore(); 
    
    // board.refresh();
    refresh();
}

void Game::exitGame() {
    endwin();
    exit(0);
}


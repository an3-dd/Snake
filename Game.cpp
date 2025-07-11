#include "Game.hpp"

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

    // Default starting direction
    currentDirection = UP; 

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

    Position centered(0, 0);
    Position bufferPos(7, 0);
    board.addStringAt(centered, score);
    board.addStringAt(bufferPos, buffer);
    refresh();
}


void Game::printTimer() {
    int elapsedPause = 0;

    // calculate elapsed time based on game state
    if (gameState == onMenu && pauseTime > 0) {
        elapsedPause = (int)(pauseTime - startTime);
    } else {
        elapsedPause = (int)(time(nullptr) - startTime);
    }

    // calculate seconds left
    int secondsLeft = timeLimit - elapsedPause;
    if (secondsLeft < 0) secondsLeft = 0;

    // format the timer as min:sec
    int min = secondsLeft / 60;
    int sec = secondsLeft % 60;
    char buffer[16];
    sprintf(buffer, "%02d:%02d", min, sec);

    char timer[] = {"Timer: "};

    Position centered(WIDTH - 12, 0);
    Position bufferPos(WIDTH - 5, 0);
    board.addStringAt(centered, timer);
    board.addStringAt(bufferPos, buffer);
    refresh();
}



void Game::openMenu(){
    // pause the timer
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
    initPrintSnake();
    spawnApples();
    printScore();
    refresh();

    // TIMER SETUP
    if (pauseTime > 0) {
        // resume timer
        startTime += (time(nullptr) - pauseTime);
    } else {
        startTime = time(nullptr);
    }
    pauseTime = 0;
    printTimer();
    refresh();

    char tornamenu[] = {"PREMI M PER IL MENU"};
    Position centered(center.x - 10, HEIGHT-1);
    board.addStringAt(centered, tornamenu);
    refresh();

    // time between moves
    int baseDelay = 200;

    int speedMult = 1;
    int scelta = menu.getCurrentLevel().diff;

    if (scelta == 0) speedMult = menu.getCurrentLevel().diff+1;
    else if (scelta == 1) speedMult = menu.getCurrentLevel().diff+2;
    else if (scelta == 2) speedMult = menu.getCurrentLevel().diff+3;

    // don't block on input
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
    if (board.isEmpty(p)) board.addCharAt(p, this->apple[0].getIcon(), 1); // 1 = red
}

void Game::removeApple(Position p){
    if (board.getCharAt(p) == this->apple[0].getIcon()) board.rmCharAt(p);
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
    board.addCharAt(center, this->snake.getHeadIcon(), 2); // 2 = green

    //add body
    //delta is the position where to spawn the next segment
    Position delta = center; 
    for(int i=1; i<SNAKE_LENGTH; i++){
        delta.y = center.y+i;
        board.addCharAt(delta, this->snake.getBodyIcon(), 2);
    }
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

    //Apple check before placing snake head
    bool ateApple = false;

    int i = 0;
    bool done = false;

    while (i < APPLE_COUNT && !done){
        if (apple[i].getPosition() == newHead) {

            // assign score based on difficulty
            int scelta = menu.getCurrentLevel().diff;
            if (scelta == 0) score += 1;
            else if (scelta == 1) score += 3;
            else if (scelta == 2) score += 5;

            ateApple = true;
            removeApple(apple[i].getPosition());

            Position newPos;

            //respawn apple if spawn has failed
            do {
                newPos = randomPosition();
            } while (!board.isEmpty(newPos));
            apple[i] = Apple(newPos);
            printApple(newPos);
            done = true;
        }
        i++;
    }

    //draw body and head
    board.addCharAt(previousHead, snake.getBodyIcon(), 2); // 2 = green
    board.addCharAt(snake.getHead(), snake.getHeadIcon(), 2);

    //if an apple was eaten, update the score
    if (ateApple) printScore(); 
    
    refresh();
}

void Game::exitGame() {
    endwin();
    exit(0);
}


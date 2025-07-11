#pragma once

#include <ncurses.h>
#include "Const.hpp"
#include "Apple.hpp"
#include "Snake.hpp"
#include "Menu.hpp"
#include "Scriba.hpp"

//for the randomizer
#include "ctime"

enum GameState {onGame, onMenu, onPause, onDeathScreen};

class Game{

    protected:

    Board board;
    Menu menu;
    Position center;
   
    // there are x apples on the screen, when one is eaten it respawns in another point
    Apple apple[APPLE_COUNT];
    Snake snake;
    Scriba scriba;

    GameState gameState;

    int score;

    // stores the current direction for auto-move
    Direction currentDirection; 


    // sets the current computer time as the start time
    time_t startTime;

    // 5 minutes in seconds
    int timeLimit = 300; 

    // if the game is paused, this is the time when it was paused
    time_t pauseTime = 0;

    // if the game is paused, this is the time when it was started again
    int timePaused = 0;

    public:

    Game();


    // print the score above the window
    void printScore();

    void startGame();

    void exitGame();

    Scriba getScriba();

    Board getBoard();

    Menu getMenu();

    void openMenu();

    // process the menu input
    void processInput();

    // process the deathMenu input
    void processInputDeath();

    void openDeathMenu();

    GameState getGameState();

    Position randomPosition();

    
    //Apple methods

    void printApple(Position p);

    void removeApple(Position p);

    void spawnApples();
    

    //Snake methods

    void initPrintSnake();

    void updateSnake(Direction inputDirection);

    void printTimer();


};



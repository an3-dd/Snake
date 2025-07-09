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
   
    Apple apple[APPLE_COUNT]; //there are x apples on the screen, when one is eaten it respawns in another point
    Snake snake;
    Scriba scriba;

    GameState gameState;

    int score;

    Direction currentDirection; // stores the current direction for auto-move

    time_t startTime;
    int timeLimit = 300; // 5 minutes in seconds
    time_t pauseTime = 0;
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



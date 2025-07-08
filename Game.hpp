#pragma once


#include <ncurses.h>
#include "Const.hpp"
#include "Apple.hpp"
#include "Snake.hpp"
#include "Menu.hpp"
#include "Scriba.hpp"

//for the randomizer
// #include "cstdlib"
// #include "ctime"

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

    // inutile perche lo trovi in getMenu().getCurrentLevel().bonus;
    // int bonus; //bonus is the score multiplier based on level

    Direction currentDirection; // stores the current direction for auto-move

    public:

    Game();


    // // print the score above the window
    void printScore(int score);

    // clear the score from the board
    void clearScore();    


    // tentativo di fix bug doppio clic on menu
    void begin();

    void startGame();

    void exitGame();

    void showScore();

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


};



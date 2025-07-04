#pragma once


#include <ncurses.h>
#include "Const.hpp"
#include "Apple.hpp"
#include "Snake.hpp"
#include "Menu.hpp"
#include "Scriba.hpp"

//for the randomizer
#include "cstdlib"
#include "ctime"

enum GameState {onGame, onMenu, onPause, onDeathScreen};

class Game{


    protected:

    // variabili che servono a gestire il gioco
    int velocita = 0;


    Board board;
    Menu menu;
    Position center;
   
    Apple apple[APPLE_COUNT]; //there are x apples on the screen, when one is eaten it respawns in another point
    Snake snake;
    Scriba scriba;

    GameState gameState; // bool gameOver;

    int score;

    // inutile perche lo trovi in getMenu().getCurrentLevel().bonus;
    // int bonus; //bonus is the score multiplier based on level

    public:

    Game();

    void startGame();

    void exitGame();

    void showScore();

    Scriba getScriba();

    Board getBoard();

    Menu getMenu();

    void openMenu();

    void processInput();

    void openDeathScreen();

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



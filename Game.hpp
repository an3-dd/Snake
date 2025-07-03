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

    Board board;
    Menu menu;
    Position center;
   
    Apple apple[APPLE_COUNT]; //there are x apples on the screen, when one is eaten it respawns in another point
    Snake snake;
    Scriba scriba;

    //uso un enum al posto di un booleano per capire in che stato si trova il gioco
    GameState gameState; // bool gameOver;

    int score;

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



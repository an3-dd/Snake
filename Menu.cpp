#pragma once

#include "Menu.hpp"
#include <cstring>
#include <menu.h>

Menu::Menu(){

    initBoard();
    initLevels();
    cleanPodium();

}

void Menu::initBoard(){
    menuBoard.init();
}

void Menu::initLevels(){

    level = new Levels;
    level->prev = nullptr;
    level->diff = 1;
    level->timeSec *= level->diff;
    strcpy(level->name, "facile");
    
    level->next = new Levels;
    level->next->prev = level;
    level->next->diff = 2;
    level->next->timeSec *= level->next->diff;
    strcpy(level->next->name, "medio");

    level->next->next = new Levels;
    level->next->next->prev = level->next;
    level->next->next->diff = 3;
    level->next->next->timeSec *= level->next->next->diff;
    strcpy(level->next->next->name, "difficile");
    level->next->next->next = nullptr;

}

int Menu::getChoice(){
    return this->choice;
}







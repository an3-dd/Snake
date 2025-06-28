#pragma once

#include "Menu.hpp"
#include "Const.hpp"
#include "Position.hpp"
#include <cstring>
#include <menu.h>
#include <iostream>
#include <ncurses.h>

using namespace std;

Menu::Menu(){

    initBoard();
    initLevels();
    cleanPodium();

}


bool Menu::addLevel(int d, char name[]) {

  bool done = false;

  Levels *n = new Levels;
  n->diff = d;
  strcpy(n->name, name);
  n->timeSec *= n->diff;
  n->bonus *= n->diff;
  n->prev = nullptr;
  n->next = nullptr;

  Levels *p = head;

  if (head == nullptr) {
    head = new Levels;
    head = n;
    return true;
  }
  else {

    while (!done) {
      if (p->diff == n->diff) {
        return false;
      } else {
        if (n->diff < p->diff) {
          if (p->prev == nullptr) {
            p->prev = n;
            n->next = p;
            n->prev = nullptr;
            head = n;
            done = true;
          } else {
            p = p->prev;
            continue;
          }
        } else {
          if (p->next == nullptr) {
            p->next = n;
            n->prev = p;
            n->next = nullptr;
            done = true;
          } else {
            p = p->next;
            continue;
          }
        }
      }
    }
  }
  return done;
}

void Menu::printLevels() {

  Levels *p = head;

  while (p != nullptr) {

    cout << "nome livello: " << p->name << endl;
    cout << "difficolta: " << p->diff << endl;
    cout << "bonus: " << p->bonus << endl;
    cout << "durata livello: " << p->timeSec << endl;
    cout << endl;
    p = p->next;
  }
}

void Menu::initLevels(){

    char facile[] = "facile";
    char medio[] = "medio";
    char difficile[] = "difficile";

    addLevel(1, facile);
    addLevel(2, medio);
    addLevel(3, difficile);
}


void Menu::initBoard(){
    menuBoard.init();
}

void Menu::addVoices(){

    char* voices[] = {"GIOCA", "CLASSIFICA", "SELEZIONA LIVELLO", "ESCI"};
    int numVoices = 4;
    int selected = 0;
    int input;
    Position center;
    center.x = WIDTH/2;
    center.y = HEIGHT/2; 

    keypad(menuBoard.getWin(), TRUE);
    curs_set(0);

    while (1){

      menuBoard.clear();

      for (int i = 0; i < numVoices; i++){
        if (i == selected){
          wattron(menuBoard.getWin(), A_REVERSE);
          menuBoard.addStringAt(center, voices[i]);
          wattroff(menuBoard.getWin(), A_REVERSE);
        }
        else menuBoard.addStringAt(center, voices[i]);
      }

      menuBoard.refresh();

      input = menuBoard.getInput();

      switch (input){
        case KEY_UP:
          selected = (selected - 1 + numVoices) % numVoices;
          break;
        case KEY_DOWN:
          selected = (selected + 1) % numVoices;
          break;
        case '\n':
          this->choice = selected;
          return;
      }
    }
}

void Menu::open(){
    initBoard();
}

void Menu::selectLevel(){

}

int Menu::getChoice(){
    return this->choice;
}







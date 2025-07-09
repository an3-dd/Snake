// #pragma once

#include "Menu.hpp"
#include "Const.hpp"
#include "Position.hpp"
#include <cstring>
#include <iostream>
#include <menu.h>
#include <ncurses.h>

using namespace std;

Menu::Menu() {
  initLevels();
}

Menu::~Menu() {
    Levels* p = head;
    while (p != nullptr) {
        Levels* next = p->next;
        delete p;
        p = next;
    }
}

void Menu::setCurrentLevel(){

  Levels *p = head;

  while (p != nullptr){

    if (p->diff == choice){
      currentLevel.diff = p->diff;
      strcpy(currentLevel.name, p->name);
    }

    p = p->next;
  }
  cerr << "qualcosa è andato storto";
}


Levels Menu::getCurrentLevel(){
  return this->currentLevel;
}

// aggiunge i livelli alla lista bidirezionale
bool Menu::addLevel(int d, char name[]) {

  bool done = false;

  Levels *n = new Levels;
  n->diff = d;
  strcpy(n->name, name);
  n->prev = nullptr;
  n->next = nullptr;

  Levels *p = head;

  if (head == nullptr) {
    head = n;
    done = true;
  } else {

    while (!done) {
      if (p->diff == n->diff) {
        delete n;
        done = false;
      } else {
        if (n->diff < p->diff) {
          if (p->prev == nullptr) {
            n->next = p;
            p->prev = n;
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


void Menu::initLevels() {

  char facile[] = "facile";
  char medio[] = "medio";
  char difficile[] = "difficile";

  addLevel(0, facile);
  addLevel(1, medio);
  addLevel(2, difficile);
}

// Board::init()
void Menu::initBoard() { menuBoard.init(); }

void Menu::showOptions() {

  char gioca[] = "GIOCA";
  char classifica[] = "VEDI CLASSIFICA";
  char seleziona[] = "SELEZIONA LIVELLO";
  char esci[] = "ESCI";

  char *voices[] = {gioca, classifica, seleziona, esci};
  int numVoices = 4;
  int selected = 0;
  int input = 0;

  Position center;
  Position pos;
  center.x = WIDTH / 2;
  center.y = HEIGHT / 2;
  keypad(menuBoard.getWin(), TRUE);
  curs_set(0);

  bool done = false;
  while (!done) {
    menuBoard.clear();
    for (int i = 0; i < numVoices; i++) {
      int len = strlen(voices[i]);
      pos.x = center.x - len / 2; // centra la voce rispetto all'asse x
      pos.y = (HEIGHT - numVoices) / 2 + i;
      if (i == selected) {
        wattron(menuBoard.getWin(), A_REVERSE);
        menuBoard.addStringAt(pos, voices[i]);
        wattroff(menuBoard.getWin(), A_REVERSE);
      } else
        menuBoard.addStringAt(pos, voices[i]);
    }
    refresh();
    input = menuBoard.getInput();

    if (input == KEY_UP) selected = (selected - 1 + numVoices) % numVoices;
    else if (input == KEY_DOWN) selected = (selected + 1) % numVoices;
    else if (input == '\n') {
      this->choice = selected;
      done = true;
    }

  }
}

void Menu::showDeathOptions(){

  char menu[] = "TORNA AL MENU";
  char esci[] = "ESCI";

  char *voices[] = { menu, esci};
  int numVoices = 2;
  int selected = 0;
  int input = 0;

  Position center;
  Position pos;
  center.x = WIDTH / 2;
  center.y = HEIGHT / 2;
  keypad(menuBoard.getWin(), TRUE);
  curs_set(0);

  bool done = false;
  while (!done) {
    menuBoard.clear();
    for (int i = 0; i < numVoices; i++) {
      pos.x = center.x;
      pos.y = (HEIGHT - numVoices) / 2 + i;
      if (i == selected) {
        wattron(menuBoard.getWin(), A_REVERSE);
        menuBoard.addStringAt(pos, voices[i]);
        wattroff(menuBoard.getWin(), A_REVERSE);
      } else
        menuBoard.addStringAt(pos, voices[i]);
    }

    refresh();
    input = menuBoard.getInput();
    if (input == KEY_UP) selected = (selected - 1 + numVoices) % numVoices;
    else if (input == KEY_DOWN) selected = (selected + 1) % numVoices;
    else if (input == '\n'){
      this->choice = selected;
      done = true;
    }

  }
}

void Menu::open() {
  menuBoard.clear();
  refresh();
  showOptions();
}

void Menu::openDeath(){
  menuBoard.clear();
  refresh();
  showDeathOptions();
}

void Menu::showLevels() {

  char facile[] = "FACILE";
  char medio[] = "MEDIO";
  char difficile[] = "DIFFICILE";
  char indietro[] = "INDIETRO";

  char *voices[] = {facile, medio, difficile, indietro};
  int numVoices = 4;
  int selected = 0;
  int input;

  Position center;
  Position pos;
  center.x = WIDTH / 2;
  center.y = HEIGHT / 2;
  keypad(menuBoard.getWin(), TRUE);
  curs_set(0);
  while (true) {
    menuBoard.clear();
    for (int i = 0; i < numVoices; i++) {
      int len = strlen(voices[i]);
      pos.x = center.x - len / 2; // centra la voce rispetto all'asse x
      pos.y = (HEIGHT - numVoices) / 2 + i;
      if (i == selected) {
        wattron(menuBoard.getWin(), A_REVERSE);
        menuBoard.addStringAt(pos, voices[i]);
        wattroff(menuBoard.getWin(), A_REVERSE);
      } else
        menuBoard.addStringAt(pos, voices[i]);
    }

    refresh();
    input = menuBoard.getInput();
    if (input == KEY_UP) selected = (selected - 1 + numVoices) % numVoices;
    else if (input == KEY_DOWN) selected = (selected + 1) % numVoices;
    else if (input == '\n'){
      this->choice = selected;
      setCurrentLevel();
      resetChoice();
      return;
    }

  }
}


int Menu::getChoice() { return this->choice; }

void Menu::resetChoice() { this->choice = -1; }

Board Menu::getMenuBoard(){
  return menuBoard;
}

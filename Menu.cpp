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
  // initBoard();
  initLevels();
}

// aggiunge i livelli alla lista bidirezionale
bool Menu::addLevel(int d, char name[]) {

  bool done = false;

  Levels *n = new Levels;
  n->diff = d;
  strcpy(n->name, name);
  n->timeSec *= 10 * n->diff;
  n->bonus = 5 * (n->diff + 1);
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

int Menu::getLevel() { return level; }

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
  while (true) { // DA TOGLIERE PRE
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
    // menuBoard.refresh();
    refresh();
    input = menuBoard.getInput();
    switch (input) {
    case KEY_UP:
      selected = (selected - 1 + numVoices) % numVoices;
      break;
    case KEY_DOWN:
      selected = (selected + 1) % numVoices;
      break;
    case '\n':
      this->choice = selected;
      return;
    default:
      break;
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
  while (true) { // DA TOGLIERE PRE
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
    // menuBoard.refresh();
    refresh();
    input = menuBoard.getInput();
    switch (input) {
    case KEY_UP:
      selected = (selected - 1 + numVoices) % numVoices;
      break;
    case KEY_DOWN:
      selected = (selected + 1) % numVoices;
      break;
    case '\n':
      this->choice = selected;
      return;
    default:
      break;
    }
  }
}

void Menu::open() {
  menuBoard.clear();
  // menuBoard.refresh();
  refresh();
  showOptions();
}

void Menu::openDeath(){
  menuBoard.clear();
  // menuBoard.refresh();
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
      pos.x = center.x;
      pos.y = (HEIGHT - numVoices) / 2 + i;
      if (i == selected) {
        wattron(menuBoard.getWin(), A_REVERSE);
        menuBoard.addStringAt(pos, voices[i]);
        wattroff(menuBoard.getWin(), A_REVERSE);
      } else
        menuBoard.addStringAt(pos, voices[i]);
    }
    // menuBoard.refresh();
    refresh();
    input = menuBoard.getInput();
    switch (input) {
    case KEY_UP:
      selected = (selected - 1 + numVoices) % numVoices;
      break;
    case KEY_DOWN:
      selected = (selected + 1) % numVoices;
      break;
    case '\n':
      level = selected;
      return;
    default:
      break;
    }
  }
}


int Menu::getChoice() { return this->choice; }

void Menu::resetChoice() { this->choice = -1; }

Board Menu::getMenuBoard(){
  return menuBoard;
}

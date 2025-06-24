#include "Apple.hpp"





Apple::Apple(int x, int y){
    this->x = x;
    this->y = y;
    this->icon = '$';
}

char Apple::getIcon(){
    return this->icon;
}

int Apple::getX(){
    return this->x;
}

int Apple::getY(){
    return this->y;
}
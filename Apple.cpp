#include "Apple.hpp"

Apple::Apple(Position p){
    this->position = p;
    this->icon = '$';
}

Apple::Apple(){
    this->position = Position(0,0);
    this->icon = '$';
}


char Apple::getIcon(){
    return this->icon;
}

Position Apple::getPosition(){
    return this->position;
}
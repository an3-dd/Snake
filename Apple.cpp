#include "Apple.hpp"

Apple::Apple(Position p){
    this->position = p;
    this->icon = '$';
}

char Apple::getIcon(){
    return this->icon;
}

Position Apple::getPosition(){
    return this->position;
}
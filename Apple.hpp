#include <ncurses.h>
#include "Position.hpp"

class Apple{

    protected:

    Position position;
    char icon;

    public:

    // the econstructor of the apple
    Apple(Position);
    Apple(); //default constructor, needed for the array in game

    // return the apple's icon
    char getIcon();

    Position getPosition();

};
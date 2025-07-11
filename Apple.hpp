#include <ncurses.h>
#include "Position.hpp"

class Apple{

    protected:

    Position position;
    char icon;


    public:

    // the constructor of the apple
    Apple(Position);

    // default constructor, needed for the array in game
    Apple(); 


    // return the apple's icon
    char getIcon();

    // return the apple's position
    Position getPosition();


    
};
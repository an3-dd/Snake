#include <ncurses.h>


class Apple{

    protected:

    int x, y;
    char icon;

    public:

    // the econstructor of the apple
    Apple(int x, int y);

    // return the apple's icon
    char getIcon();

    
    int getX();

    int getY();







};
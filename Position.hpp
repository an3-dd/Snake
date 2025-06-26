#pragma once   //maybe makes errors

struct Position {
    int x;
    int y;

    Position(int x, int y){
        this->x = x;
        this->y = y;
    }

    //Default
    Position(){
        this->x = 0;
        this->y = 0;
    }
};

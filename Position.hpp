#pragma once

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

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

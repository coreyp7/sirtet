#pragma once
#include <include/Direction.h>
#include <include/Block.h>

class Piece {
    public:
        Block blocks[4]; //hardcoding rn to one type of piece
        Direction facing;

        Piece(int x, int y);
        void move(Direction dir);
        void rotateCW();

        
};
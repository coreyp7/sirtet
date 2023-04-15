#pragma once
#include <include/Direction.h>
#include <include/Block.h>

class Piece {
    public:
        Block blocks[4]; //hardcoding rn to one type of piece
        Direction facing;
        int gridHeight = 20; // hardcoded for now
        int gridWidth = 10; // hardcoded for now

        Piece(int x, int y);
        void move(Direction dir);
        void rotateCW();
        void rotateCCW();

        
};
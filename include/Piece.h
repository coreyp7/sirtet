#pragma once
#include <include/Direction.h>
#include <include/Block.h>
#include <include/Tile.h>

class Piece {
    public:
        Block blocks[4]; //hardcoding rn to one type of piece
        Direction facing;
        int gridHeight = 20; // hardcoded for now
        int gridWidth = 10; // hardcoded for now

        Piece(int x, int y, Tile (&grid)[200]);
        void move(Direction dir);
        void rotateCW();
        void rotateCCW();

        
};
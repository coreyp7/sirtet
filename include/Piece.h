#pragma once
#include <include/Direction.h>
#include <include/Block.h>
#include <include/Tile.h>
#include <include/util.h>
#include <stdio.h>
#include <array>

class Piece {
    public:
        Block blocks[4]; //hardcoding rn to one type of piece
        Direction facing;
        // int gridHeight = 20; // hardcoded for now
        // int gridWidth = 10; // hardcoded for now

        std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid;

        

        Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid);
        bool move(Direction dir);
        void rotateCW();
        void rotateCCW();
        bool isEmpty(int x, int y);
        bool isEmptyAndInBounds(int x, int y);

        
};
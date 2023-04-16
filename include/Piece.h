#pragma once
#include <include/Direction.h>
#include <include/Block.h>
#include <include/Tile.h>
#include <include/util.h>
#include <stdio.h>
#include <array>
#include <vector>

class Piece {
    public:
        //Block* blocks[4]; //hardcoding rn to one type of piece
        Direction facing;
        // int gridHeight = 20; // hardcoded for now
        // int gridWidth = 10; // hardcoded for now

        std::vector<Block *> blocks;
        std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid;

        

        Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid);
        bool move(Direction dir);
        virtual void rotateCW();
        virtual void rotateCCW();
        bool isEmpty(int x, int y);
        bool isEmptyAndInBounds(int x, int y);
        // Call when Piece has landed and control is being removed from this piece.
        // This just sets everything in this object to NULL, but leaves blocks
        // in memory (because they are cleaned up via the grid in main).
        void cleanupLanded();

        int insertBlocksAtCurrPos();
        
};
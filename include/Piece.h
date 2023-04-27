#pragma once
#include <include/Direction.h>
#include <include/Block.h>
#include <include/Tile.h>
#include <include/util.h>
#include <include/constants.h>
#include <stdio.h>
#include <array>
#include <vector>

class Piece {
    public:
        Direction facing;

        Block *blocks[4]; // the blocks that makeup this Piece (always 4)
        int blocksSize = 4; // just keeping this just in case I wanna add weird blocks or sum
        std::array<Tile, constants::GRID_WIDTH*constants::GRID_HEIGHT> *grid;

        
        Piece();
        Piece(int x, int y, std::array<Tile, constants::GRID_WIDTH*constants::GRID_HEIGHT> *grid);
        ~Piece();
        bool move(Direction dir);
        virtual void setPosition(int x, int y) = 0;
        virtual void rotateCW() = 0;
        virtual void rotateCCW() = 0;
        bool isEmpty(int x, int y);
        bool isEmptyAndInBounds(int x, int y);
        // Call when Piece has landed and control is being removed from this piece.
        // This just sets everything in this object to NULL, but leaves blocks
        // in memory (because they are cleaned up via the grid in main).
        void cleanupLanded();
        void landInstant();

        int insertBlocksAtCurrPos();
        
};
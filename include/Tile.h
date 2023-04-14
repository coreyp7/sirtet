#pragma once
#include "include/Block.h"

class Tile {
    public:
        Tile();
        Tile(int x, int y, Block *block);

        int x, y;

        Block *block; // store a block that's in this position; NULL if no block in this tile.
};
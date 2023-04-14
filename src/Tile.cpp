#include "include/Tile.h"

Tile::Tile(){

}

Tile::Tile(int x, int y, Block *block){
    this->x = x;
    this->y = y;

    this->block = block;
}
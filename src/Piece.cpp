#include "include/Piece.h"

Piece::Piece(int x, int y){
    blocks[0] = Block{x, y};
    blocks[1] = Block{x, y-1};
    blocks[2] = Block{x+1, y};
    blocks[3] = Block{x+1, y+1};
}

void Piece::move(Direction dir){
    // move piece here.
}

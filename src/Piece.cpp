#include "include/Piece.h"

Piece::Piece(int x, int y){
    blocks[0] = Block{x, y};
    blocks[1] = Block{x, y-1};
    blocks[2] = Block{x+1, y};
    blocks[3] = Block{x+1, y+1};
}

void Piece::move(Direction dir){
    int xMove = 0;
    int yMove = 0;

    switch(dir){
        case UP:
            yMove--;
            break;
        case DOWN:
            yMove++;
            break;
        case LEFT:
            xMove--;
            break;
        case RIGHT:
            xMove++;
            break;
    }

    Block *block = blocks;
    for(int i=0; i<4; i++){
        block->x += xMove;
        block->y += yMove;
        block++;
    }
}

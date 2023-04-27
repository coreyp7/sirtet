
#include "include/pieces/O_Piece.h"

O_Piece::O_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid)
: Piece(){
    // Dynamically allocated so that they stay in memory when on the grid.
    blocks[0] = (new Block{x, y});
    blocks[1] = (new Block{x+1, y});
    blocks[2] = (new Block{x, y+1});
    blocks[3] = (new Block{x+1, y+1});
    this->grid = grid;
    for(int i=0; i<blocksSize; i++){
        blocks[i]->pieceType = 'O';
    }

    facing = UP;
}

O_Piece::~O_Piece(){
    for(int i=0; i<blocksSize; i++){
        blocks[i] = NULL;
    }

    grid = NULL;
}

void O_Piece::rotateCW() {
    // do nothing 
}

void O_Piece::rotateCCW(){
}

void O_Piece::setPosition(int x, int y){
    blocks[0]->setPosition(x, y);
    blocks[1]->setPosition(x+1, y);
    blocks[2]->setPosition(x, y+1);
    blocks[3]->setPosition(x+1, y+1);
}


#include "include/Piece.h"
#include "include/util.h"

Piece::Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid){
    // Dynamically allocated so that they stay in memory when on the grid.
    blocks.push_back(new Block{x, y});
    blocks.push_back(new Block{x, y-1});
    blocks.push_back(new Block{x+1, y});
    blocks.push_back(new Block{x+1, y+1});
    this->grid = grid;

    facing = UP;
}

Piece::Piece(){
    // for when you create a Piece from a subclass and don't need anything done for you here.
}

bool Piece::move(Direction dir){
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

    // Check if there's a collision where we're going to.
    Block *block;// = blocks[0];
    for(int i=0; i<blocks.size(); i++){
        block = blocks[i];
        if(!isEmptyAndInBounds(block->x + xMove, block->y + yMove)){
            return false;
        }

        if(getTile(block->x + xMove, block->y + yMove, grid)->block != NULL){
            return false;
        }
        //block++;
    }

    //block = blocks[0];
    for(int i=0; i<blocks.size(); i++){
        block = blocks[i];
        block->x += xMove;
        block->y += yMove;
        //block++;
    }
    return true;
}

// Will return if the specified Tile position has a block in it.
bool Piece::isEmpty(int x, int y){
    return isEmptyAndInBounds(x, y);
}

bool Piece::isEmptyAndInBounds(int x, int y){
    if ( !((x >= 0 && x < GRID_WIDTH) && (y >= 0 && y < GRID_HEIGHT)) ) { // make sure its in bounds
        return false;
    }

    return(getTile(x, y, grid)->block == NULL);
}

void Piece::cleanupLanded(){
    // empty array of references to objects, they're in the grid now
    // and will be cleaned up later.
    for(int i=0; i<blocks.size(); i++){
        blocks[i] = NULL;
    }

    grid = NULL;
}

// Will insert all the Blocks of this object into its current position.
// Should only be called when a Piece has landed and you're going to get rid of it.
int Piece::insertBlocksAtCurrPos(){
    for(int i=0; i<blocks.size(); i++){
        getTile(blocks[i]->x, blocks[i]->y, grid)->block = blocks[i];
    }
}
#include "include/I_Piece.h"

I_Piece::I_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid)
: Piece(){
    // Dynamically allocated so that they stay in memory when on the grid.
    blocks[0] = (new Block{x, y});
    blocks[1] = (new Block{x+1, y});
    blocks[2] = (new Block{x+2, y});
    blocks[3] = (new Block{x+3, y});
    this->grid = grid;
    for(int i=0; i<blocksSize; i++){
        blocks[i]->pieceType = 'I';
    }

    facing = RIGHT;
}

I_Piece::~I_Piece(){
    for(int i=0; i<blocksSize; i++){
        blocks[i] = NULL;
    }

    grid = NULL;
}

void I_Piece::rotateCW() {
    // NO PIVOT ANYMORE

    switch(facing){
        case UP:

            // Check if there's a collision where we're going to.
            if(isEmpty(blocks[0]->x-2, blocks[0]->y+2) &&
                isEmpty(blocks[1]->x-1, blocks[1]->y+1) &&
                isEmpty(blocks[3]->x+1, blocks[3]->y-1)
            ){
                blocks[0]->x -= 2;
                blocks[0]->y += 2;
                blocks[1]->x -= 1;
                blocks[1]->y += 1;
                blocks[3]->x += 1;
                blocks[3]->y -= 1;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            if(isEmpty(blocks[0]->x+1, blocks[0]->y-2) &&
                isEmpty(blocks[1]->x, blocks[1]->y-1) &&
                isEmpty(blocks[2]->x-1, blocks[2]->y) &&
                isEmpty(blocks[3]->x-2, blocks[3]->y+1)
            ){
                blocks[0]->x += 1;
                blocks[0]->y -= 2;
                blocks[1]->y -= 1;
                blocks[2]->x -= 1;
                blocks[3]->x -= 2;
                blocks[3]->y += 1;
                facing = DOWN;
            } else {
                printf("not allowed");
            }
            break;
        case DOWN:
            if(isEmpty(blocks[0]->x-1, blocks[0]->y+1) &&
                isEmpty(blocks[2]->x+1, blocks[2]->y-1) &&
                isEmpty(blocks[3]->x+2, blocks[3]->y-2)
            ){
                blocks[0]->x -= 1;
                blocks[0]->y += 1;
                blocks[2]->x += 1;
                blocks[2]->y -= 1;
                blocks[3]->x += 2;
                blocks[3]->y -= 2;
                facing = LEFT;
            } else {
                printf("not allowed");
            }
            break;
        case LEFT:
            if(isEmpty(blocks[0]->x+2, blocks[0]->y-1) &&
                isEmpty(blocks[1]->x+2, blocks[1]->y) &&
                isEmpty(blocks[2]->x, blocks[2]->y+1) &&
                isEmpty(blocks[3]->x-1, blocks[3]->y+2)
            ){
                blocks[0]->x += 2;
                blocks[0]->y -= 1;
                blocks[1]->x += 1;
                blocks[2]->y += 1;
                blocks[3]->x -= 1;
                blocks[3]->y += 2;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
        }
}

void I_Piece::rotateCCW(){
    // NO PIVOT ANYMORE

    switch(facing){
        case UP:

            if(isEmpty(blocks[0]->x-2, blocks[0]->y+1) &&
                isEmpty(blocks[1]->x-1, blocks[1]->y) &&
                isEmpty(blocks[2]->x, blocks[2]->y-1) &&
                isEmpty(blocks[3]->x+1, blocks[3]->y-2)
            ){
                blocks[0]->x -= 2;
                blocks[0]->y += 1;
                blocks[1]->x -= 1;
                blocks[2]->y -= 1;
                blocks[3]->x += 1;
                blocks[3]->y -= 2;
                facing = LEFT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            if(isEmpty(blocks[0]->x+2, blocks[0]->y-2) &&
                isEmpty(blocks[1]->x+1, blocks[1]->y+1) &&
                isEmpty(blocks[3]->x-1, blocks[3]->y+1)
            ){
                blocks[0]->x += 2;
                blocks[0]->y -= 2;
                blocks[1]->x += 1;
                blocks[1]->y -= 1;
                blocks[3]->x -= 1;
                blocks[3]->y += 1;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
        case DOWN:
            
            // Check if there's a collision where we're going to.
            if(isEmpty(blocks[0]->x-1, blocks[0]->y+2) &&
                isEmpty(blocks[1]->x, blocks[1]->y+1) &&
                isEmpty(blocks[2]->x+1, blocks[1]->y) &&
                isEmpty(blocks[3]->x+2, blocks[3]->y-1)
            ){
                blocks[0]->x -= 1;
                blocks[0]->y += 2;
                blocks[1]->y += 1;
                blocks[2]->x += 1;
                blocks[3]->x += 2;
                blocks[3]->y -= 1;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }
            break;
        case LEFT:
            
            if(isEmpty(blocks[0]->x+1, blocks[0]->y-1) &&
                isEmpty(blocks[2]->x-1, blocks[2]->y+1) &&
                isEmpty(blocks[3]->x-2, blocks[3]->y+2)
            ){
                blocks[0]->x += 1;
                blocks[0]->y -= 1;
                blocks[2]->x -= 1;
                blocks[2]->y += 1;
                blocks[3]->x -= 2;
                blocks[3]->y += 2;
                facing = DOWN;
            } else {
                printf("not allowed");
            }
            break;
        }
}

void I_Piece::setPosition(int x, int y){
    blocks[0]->setPosition(x, y);
    blocks[1]->setPosition(x+1, y);
    blocks[2]->setPosition(x+2, y);
    blocks[3]->setPosition(x+3, y);
    facing = RIGHT;
}


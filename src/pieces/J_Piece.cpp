#include "include/pieces/J_Piece.h"

J_Piece::J_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid)
: Piece(){
    // Dynamically allocated so that they stay in memory when on the grid.
    blocks[0] = (new Block{x, y});
    blocks[1] = (new Block{x, y-1});
    blocks[2] = (new Block{x+1, y-1});
    blocks[3] = (new Block{x, y+1});
    this->grid = grid;
    for(int i=0; i<blocksSize; i++){
        blocks[i]->pieceType = 'J';
    }

    facing = UP;
}

J_Piece::~J_Piece(){
    for(int i=0; i<blocksSize; i++){
        blocks[i] = NULL;
    }

    grid = NULL;
}

void J_Piece::rotateCW() {
    Block pivot = *blocks[0]; // PIVOT IS 2
    // NO PIVOT ANYMORE

    switch(facing){
        case UP:

            // Check if there's a collision where we're going to.
            if(isEmpty(pivot.x-1, pivot.y) &&
                isEmpty(pivot.x+1, pivot.y) &&
                isEmpty(pivot.x+1, pivot.y+1)
            ){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y;
                blocks[2]->x = pivot.x+1;
                blocks[2]->y = pivot.y;
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y+1;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            if(isEmpty(pivot.x-1, pivot.y+1) &&
                isEmpty(pivot.x, pivot.y-1) &&
                isEmpty(pivot.x, pivot.y+1)
            ){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y+1;
                blocks[2]->x = pivot.x;
                blocks[2]->y = pivot.y-1;
                blocks[3]->x = pivot.x;
                blocks[3]->y = pivot.y+1;
                facing = DOWN;
            } else {
                printf("not allowed");
            }
            break;
        case DOWN:
            if(isEmpty(pivot.x-1, pivot.y) &&
                isEmpty(pivot.x-1, pivot.y-1) &&
                isEmpty(pivot.x+1, pivot.y)
            ){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y;
                blocks[2]->x = pivot.x-1;
                blocks[2]->y = pivot.y-1;
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y;
                facing = LEFT;
            } else {
                printf("not allowed");
            }
            break;
        case LEFT:
            if(isEmpty(pivot.x, pivot.y-1) &&
                isEmpty(pivot.x+1, pivot.y-1) &&
                isEmpty(pivot.x, pivot.y+1)
            ){
                blocks[1]->x = pivot.x;
                blocks[1]->y = pivot.y-1;
                blocks[2]->x = pivot.x+1;
                blocks[2]->y = pivot.y-1;
                blocks[3]->x = pivot.x;
                blocks[3]->y = pivot.y+1;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
        }
}

void J_Piece::rotateCCW(){
    Block pivot = *blocks[0]; // PIVOT IS 2
    // NO PIVOT ANYMORE

    switch(facing){
        case UP:
            if(isEmpty(pivot.x-1, pivot.y) &&
                isEmpty(pivot.x-1, pivot.y-1) &&
                isEmpty(pivot.x+1, pivot.y)
            ){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y;
                blocks[2]->x = pivot.x-1;
                blocks[2]->y = pivot.y-1;
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y;
                facing = LEFT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            if(isEmpty(pivot.x, pivot.y-1) &&
                isEmpty(pivot.x+1, pivot.y-1) &&
                isEmpty(pivot.x, pivot.y+1)
            ){
                blocks[1]->x = pivot.x;
                blocks[1]->y = pivot.y-1;
                blocks[2]->x = pivot.x+1;
                blocks[2]->y = pivot.y-1;
                blocks[3]->x = pivot.x;
                blocks[3]->y = pivot.y+1;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
        case DOWN:

            // Check if there's a collision where we're going to.
            if(isEmpty(pivot.x-1, pivot.y) &&
                isEmpty(pivot.x+1, pivot.y) &&
                isEmpty(pivot.x+1, pivot.y+1)
            ){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y;
                blocks[2]->x = pivot.x+1;
                blocks[2]->y = pivot.y;
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y+1;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }
            break;
        case LEFT:
            if(isEmpty(pivot.x-1, pivot.y+1) &&
                isEmpty(pivot.x, pivot.y-1) &&
                isEmpty(pivot.x, pivot.y+1)
            ){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y+1;
                blocks[2]->x = pivot.x;
                blocks[2]->y = pivot.y-1;
                blocks[3]->x = pivot.x;
                blocks[3]->y = pivot.y+1;
                facing = DOWN;
            } else {
                printf("not allowed");
            }
            break;
        }
}

void J_Piece::setPosition(int x, int y){
    blocks[0]->setPosition(x, y);
    blocks[1]->setPosition(x, y-1);
    blocks[2]->setPosition(x+1, y-1);
    blocks[3]->setPosition(x, y+1);
    facing = UP;
}


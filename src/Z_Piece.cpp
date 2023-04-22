#include "include/Z_Piece.h"

Z_Piece::Z_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid)
: Piece(){
    // Dynamically allocated so that they stay in memory when on the grid.
    blocks[0] = (new Block{x, y});
    blocks[1] = (new Block{x+1, y});
    blocks[2] = (new Block{x, y+1});
    blocks[3] = (new Block{x+1, y-1});
    this->grid = grid; 
    for(int i=0; i<blocksSize; i++){
        blocks[i]->pieceType = 'Z';
    }

    facing = UP;
}

Z_Piece::~Z_Piece(){
    for(int i=0; i<blocksSize; i++){
        blocks[i] = NULL;
    }

    grid = NULL;
}

void Z_Piece::rotateCW() {
    Block pivot = *blocks[0];
    switch(facing){
        case UP:
            // move 0 & 1
            if(isEmpty(pivot.x-1, pivot.y) &&
                isEmpty(pivot.x, pivot.y+1) &&
                isEmpty(pivot.x+1, pivot.y+1)){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y;
                blocks[2]->x = pivot.x;
                blocks[2]->y = pivot.y+1;
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y+1;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            // move 0 & 3
            
            if(isEmpty(pivot.x, pivot.y-1) &&
                isEmpty(pivot.x-1, pivot.y+1)){
                blocks[2]->x = pivot.x;
                blocks[2]->y = pivot.y-1;
                blocks[3]->x = pivot.x-1;
                blocks[3]->y = pivot.y+1;
                facing = DOWN;
            } else {
                printf("not allowed");
            }

            break;
        case DOWN:
            // move 0 & 3

            if(isEmpty(pivot.x-1, pivot.y-1) &&
                isEmpty(pivot.x+1, pivot.y)
            ){
                blocks[1]->x = pivot.x+1;
                blocks[1]->y = pivot.y;
                blocks[3]->x = pivot.x-1;
                blocks[3]->y = pivot.y-1;
                facing = LEFT;
            } else {
                printf("not allowed");
            }

            break;
        case LEFT:
            // move 0 & 1

            if(isEmpty(pivot.x, pivot.y+1) &&
                isEmpty(pivot.x+1, pivot.y-1)
            ){
                blocks[2]->x = pivot.x;
                blocks[2]->y = pivot.y+1;
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y-1;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
    }
}

void Z_Piece::rotateCCW(){
    Block pivot = *blocks[0];
    switch(facing){
        case UP:
            // move 0 & 1
            if(isEmpty(pivot.x+1, pivot.y) &&
                isEmpty(pivot.x, pivot.y-1) &&
                isEmpty(pivot.x-1, pivot.y-1)){
                blocks[1]->x = pivot.x+1;
                blocks[1]->y = pivot.y;
                blocks[2]->x = pivot.x;
                blocks[2]->y = pivot.y-1;
                blocks[3]->x = pivot.x-1;
                blocks[3]->y = pivot.y-1;
                facing = LEFT;
            } else {
                printf("not allowed");
            }

            break;
        case LEFT:
            // move 0 & 1
            if(isEmpty(pivot.x-1, pivot.y) &&
                isEmpty(pivot.x-1, pivot.y+1)
            ){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y;
                blocks[3]->x = pivot.x-1;
                blocks[3]->y = pivot.y+1;
                facing = DOWN;
            } else {
                printf("not allowed");
            }
            break;
        case DOWN:
            // move 0 & 3

            if(isEmpty(pivot.x, pivot.y+1) &&
                isEmpty(pivot.x+1, pivot.y+1)
            ){
                blocks[2]->x = pivot.x;
                blocks[2]->y = pivot.y+1;
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y+1;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            // move 0 & 3
            
            if(isEmpty(pivot.x+1, pivot.y) &&
                isEmpty(pivot.x+1, pivot.y-1)){
                blocks[1]->x = pivot.x+1;
                blocks[1]->y = pivot.y;
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y-1;
                facing = UP;
            } else {
                printf("not allowed");
            }

            break;
    }
}

void Z_Piece::setPosition(int x, int y){
    blocks[0]->setPosition(x, y);
    blocks[1]->setPosition(x+1, y);
    blocks[2]->setPosition(x, y+1);
    blocks[3]->setPosition(x+1, y-1);
    facing = UP;
}


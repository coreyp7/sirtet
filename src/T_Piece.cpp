#include "include/T_Piece.h"

T_Piece::T_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid)
: Piece(){
    // Dynamically allocated so that they stay in memory when on the grid.
    blocks[0] = (new Block{x, y});
    blocks[1] = (new Block{x-1, y});
    blocks[2] = (new Block{x, y-1});
    blocks[3] = (new Block{x+1, y});
    this->grid = grid;

    facing = UP;
}

T_Piece::~T_Piece(){
    for(int i=0; i<blocksSize; i++){
        blocks[i] = NULL;
    }

    grid = NULL;
}

void T_Piece::rotateCW() {
    Block pivot = *blocks[0]; // PIVOT IS 0: center of t block which never moves

    switch(facing){
        case UP:
            // Check if there's a collision where we're going to.
            if(isEmpty(pivot.x, pivot.y+1)){
                blocks[1]->x = pivot.x;
                blocks[1]->y = pivot.y+1;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            if(isEmpty(pivot.x-1, pivot.y)){
                blocks[2]->x = pivot.x-1;
                blocks[2]->y = pivot.y;
                facing = DOWN;
            } else {
                printf("not allowed");
            }
            break;
        case DOWN: // this one has the most moves
            if(isEmpty(pivot.x-1, pivot.y) &&
                isEmpty(pivot.x, pivot.y-1) &&
                isEmpty(pivot.x, pivot.y+1)
            ){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y;
                blocks[2]->x = pivot.x;
                blocks[2]->y = pivot.y-1;
                blocks[3]->x = pivot.x;
                blocks[3]->y = pivot.y+1;
                facing = LEFT;
            } else {
                printf("not allowed");
            }
            break;
        case LEFT:
            if(isEmpty(pivot.x+1, pivot.y)){
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
        }
}

void T_Piece::rotateCCW(){
    Block pivot = *blocks[0]; // PIVOT IS 0: center of t block which never moves

    switch(facing){
        case UP:
            // Check if there's a collision where we're going to.
            if(isEmpty(pivot.x-1, pivot.y) &&
                isEmpty(pivot.x, pivot.y-1) && 
                isEmpty(pivot.x, pivot.y+1)
            ){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y;
                blocks[2]->x = pivot.x;
                blocks[2]->y = pivot.y-1;
                blocks[3]->x = pivot.x;
                blocks[3]->y = pivot.y+1;
                facing = LEFT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            printf("pivot.x-1:%i, pivot.y:%i", pivot.x-1, pivot.y);
            if(isEmpty(pivot.x-1, pivot.y)){
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
        case DOWN:
            if(isEmpty(pivot.x, pivot.y-1)){
                blocks[2]->x = pivot.x;
                blocks[2]->y = pivot.y-1;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }
            break;
        case LEFT:
            if(isEmpty(pivot.x, pivot.y+1) && 
                isEmpty(pivot.x-1, pivot.y) &&
                isEmpty(pivot.x+1, pivot.y)
            ){
                blocks[1]->x = pivot.x;
                blocks[1]->y = pivot.y+1;
                blocks[2]->x = pivot.x-1;
                blocks[2]->y = pivot.y;
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y;
                facing = DOWN;
            } else {
                printf("not allowed");
            }
        }
}

void T_Piece::setPosition(int x, int y){
    blocks[0]->setPosition(x, y);
    blocks[1]->setPosition(x-1, y);
    blocks[2]->setPosition(x, y-1);
    blocks[3]->setPosition(x+1, y);
    facing = UP;
}

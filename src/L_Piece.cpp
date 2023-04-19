#include "include/L_Piece.h"

L_Piece::L_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid)
: Piece(){
    // Dynamically allocated so that they stay in memory when on the grid.
    blocks[0] = (new Block{x, y});
    blocks[1] = (new Block{x+1, y});
    blocks[2] = (new Block{x, y-1});
    blocks[3] = (new Block{x, y-2});
    this->grid = grid;

    facing = UP;
}

L_Piece::~L_Piece(){
    for(int i=0; i<blocksSize; i++){
        blocks[i] = NULL;
    }

    grid = NULL;
}

void L_Piece::rotateCW() {
    Block pivot = *blocks[2]; // PIVOT IS 2
    // NO PIVOT ANYMORE

    switch(facing){
        case UP:

            // Check if there's a collision where we're going to.
            if(isEmpty(pivot.x-1, pivot.y) &&
                isEmpty(pivot.x-1, pivot.y+1) &&
                isEmpty(pivot.x+1, pivot.y)
            ){
                blocks[0]->x = pivot.x-1;
                blocks[0]->y = pivot.y;
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y+1;
                blocks[3]->x = pivot.x+1;
                blocks[3]->y = pivot.y;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            if(isEmpty(pivot.x, pivot.y-1) &&
                isEmpty(pivot.x-1, pivot.y-1) &&
                isEmpty(pivot.x, pivot.y+1)
            ){
                blocks[0]->x = pivot.x;
                blocks[0]->y = pivot.y-1;
                blocks[1]->x = pivot.x-1;
                blocks[1]->y = pivot.y-1;
                blocks[3]->x = pivot.x;
                blocks[3]->y = pivot.y+1;
                facing = DOWN;
            } else {
                printf("not allowed");
            }
            break;
        case DOWN:
            if(isEmpty(pivot.x+1, pivot.y) &&
                isEmpty(pivot.x+1, pivot.y-1) &&
                isEmpty(pivot.x-1, pivot.y)
            ){
                blocks[0]->x = pivot.x+1;
                blocks[0]->y = pivot.y;
                blocks[1]->x = pivot.x+1;
                blocks[1]->y = pivot.y-1;
                blocks[3]->x = pivot.x-1;
                blocks[3]->y = pivot.y;
                facing = LEFT;
            } else {
                printf("not allowed");
            }
            break;
        case LEFT:
            if(isEmpty(pivot.x, pivot.y+1) &&
                isEmpty(pivot.x+1, pivot.y+1) &&
                isEmpty(pivot.x, pivot.y-1)
            ){
                blocks[0]->x = pivot.x;
                blocks[0]->y = pivot.y+1;
                blocks[1]->x = pivot.x+1;
                blocks[1]->y = pivot.y+1;
                blocks[3]->x = pivot.x;
                blocks[3]->y = pivot.y-1;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
        }
}

void L_Piece::rotateCCW(){

    switch(facing){
        case UP:
            // move 0 & 1

            if(isEmpty(blocks[1]->x+2, blocks[1]->y+1) &&
                isEmpty(blocks[0]->x, blocks[0]->y+1)){
                blocks[0]->y++;
                blocks[1]->x += 2;
                blocks[1]->y += 1;
                facing = LEFT;
            } else {
                printf("not allowed");
            }

            break;
        case LEFT:
            // move 0 & 3
            
            if(isEmpty(blocks[0]->x+2, blocks[0]->y) &&
                isEmpty(blocks[3]->x, blocks[3]->y-2)){
                blocks[0]->x += 2;
                blocks[3]->y -= 2;
                facing = DOWN;
            } else {
                printf("not allowed");
            }

            break;
        case DOWN:
            // move 0 & 3

            if(isEmpty(blocks[0]->x-1, blocks[0]->y-2) &&
                isEmpty(blocks[1]->x, blocks[1]->y-1) &&
                isEmpty(blocks[3]->x-1, blocks[3]->y+1)
            ){
                blocks[3]->x--;
                blocks[3]->y++;
                blocks[1]->y--;
                blocks[0]->y -= 2;
                blocks[0]->x--;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            // move 0 & 1

            if(isEmpty(blocks[0]->x-1, blocks[0]->y+1) &&
                isEmpty(blocks[1]->x-2, blocks[1]->y) &&
                isEmpty(blocks[3]->x+1, blocks[3]->y+1)
            ){
                blocks[0]->x--;
                blocks[0]->y++;
                blocks[1]->x -= 2;
                blocks[3]->x++;
                blocks[3]->y++;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
    }
}

void L_Piece::setPosition(int x, int y){
    blocks[0]->setPosition(x, y);
    blocks[1]->setPosition(x, y-1);
    blocks[2]->setPosition(x+1, y);
    blocks[3]->setPosition(x+1, y+1);
}


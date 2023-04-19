#include "include/S_Piece.h"

S_Piece::S_Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid)
: Piece(){
    // Dynamically allocated so that they stay in memory when on the grid.
    blocks[0] = (new Block{x, y});
    blocks[1] = (new Block{x, y-1});
    blocks[2] = (new Block{x+1, y});
    blocks[3] = (new Block{x+1, y+1});
    this->grid = grid;

    facing = UP;
}

S_Piece::~S_Piece(){
    for(int i=0; i<blocksSize; i++){
        blocks[i] = NULL;
    }

    grid = NULL;
}

void S_Piece::rotateCW() {
    Block pivot = *blocks[2]; // PIVOT IS 2

    switch(facing){
        case UP:
            // move 0 & 1

            // HEY COREY:
            // do the same thing you did in move here.
            // feels inefficient but is a proven way to check for collision.
            // shouldn't ever be very much, so should be good.

            // Check if there's a collision where we're going to.
            if(isEmpty(pivot.x, pivot.y-1) &&
                isEmpty(pivot.x+1, pivot.y-1) &&
                isEmpty(pivot.x-1, pivot.y)
            ){
                blocks[0]->x = pivot.x;
                blocks[0]->y = pivot.y-1;
                blocks[1]->x = pivot.x+1;
                blocks[1]->y = pivot.y-1;
                blocks[3]->x = pivot.x-1;
                blocks[3]->y = pivot.y;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            if(isEmpty(pivot.x+1, pivot.y+1) &&
                isEmpty(pivot.x+1, pivot.y) &&
                isEmpty(pivot.x, pivot.y-1)
            ){
                blocks[0]->x = pivot.x+1;
                blocks[0]->y = pivot.y+1;
                blocks[1]->x = pivot.x+1;
                blocks[1]->y = pivot.y;
                blocks[3]->x = pivot.x;
                blocks[3]->y = pivot.y-1;
                facing = DOWN;
            } else {
                printf("not allowed");
            }
            break;
        case DOWN:
            if(isEmpty(blocks[0]->x - 2, blocks[0]->y) &&
                isEmpty(blocks[3]->x, blocks[3]->y+2)
            ){
                blocks[0]->x -= 2;
                blocks[3]->y += 2;
                facing = LEFT;
            } else {
                printf("not allowed");
            }
            break;
        case LEFT:
            if(isEmpty(blocks[0]->x, blocks[0]->y-1) &&
                isEmpty(blocks[1]->x-2, blocks[1]->y-1)
            ){
                blocks[0]->y--;
                blocks[1]->x -= 2;
                blocks[1]->y--;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
        }
}

void S_Piece::rotateCCW(){

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

void S_Piece::setPosition(int x, int y){
    blocks[0]->setPosition(x, y);
    blocks[1]->setPosition(x, y-1);
    blocks[2]->setPosition(x+1, y);
    blocks[3]->setPosition(x+1, y+1);
    facing = UP;
}


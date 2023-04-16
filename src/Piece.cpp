#include "include/Piece.h"
#include "include/util.h"

Piece::Piece(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid){
    blocks[0] = Block{x, y};
    blocks[1] = Block{x, y-1};
    blocks[2] = Block{x+1, y};
    blocks[3] = Block{x+1, y+1};

    this->grid = grid;

    facing = UP;
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

    // Check if there's a collision where we're going to.
    Block *block = blocks;
    for(int i=0; i<4; i++){
        if(getTile(block->x + xMove, block->y + yMove, grid)->block != NULL){
            return;
        }
        block++;
    }

    block = blocks;
    for(int i=0; i<4; i++){
        block->x += xMove;
        block->y += yMove;
        block++;
    }
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

void Piece::rotateCW(){
    Block pivot = blocks[2]; // PIVOT IS 2

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
                blocks[0].x = pivot.x;
                blocks[0].y = pivot.y-1;
                blocks[1].x = pivot.x+1;
                blocks[1].y = pivot.y-1;
                blocks[3].x = pivot.x-1;
                blocks[3].y = pivot.y;
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
                blocks[0].x = pivot.x+1;
                blocks[0].y = pivot.y+1;
                blocks[1].x = pivot.x+1;
                blocks[1].y = pivot.y;
                blocks[3].x = pivot.x;
                blocks[3].y = pivot.y-1;
                facing = DOWN;
            } else {
                printf("not allowed");
            }
            break;
        case DOWN:
            if(isEmpty(blocks[0].x - 2, blocks[0].y) &&
                isEmpty(blocks[3].x, blocks[3].y+2)
            ){
                blocks[0].x -= 2;
                blocks[3].y += 2;
                facing = LEFT;
            } else {
                printf("not allowed");
            }
            break;
        case LEFT:
            if(isEmpty(blocks[0].x, blocks[0].y-1) &&
                isEmpty(blocks[1].x-2, blocks[1].y-1)
            ){
                blocks[0].y--;
                blocks[1].x -= 2;
                blocks[1].y--;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
    }
}

// TODO: move this into implementations of abstract class (whatever that is in c++)
void Piece::rotateCCW(){

    switch(facing){
        case UP:
            // move 0 & 1

            if(isEmpty(blocks[1].x+2, blocks[1].y+1) &&
                isEmpty(blocks[0].x, blocks[0].y+1)){
                blocks[0].y++;
                blocks[1].x += 2;
                blocks[1].y += 1;
                facing = LEFT;
            } else {
                printf("not allowed");
            }

            break;
        case LEFT:
            // move 0 & 3
            
            if(isEmpty(blocks[0].x+2, blocks[0].y) &&
                isEmpty(blocks[3].x, blocks[3].y-2)){
                blocks[0].x += 2;
                blocks[3].y -= 2;
                facing = DOWN;
            } else {
                printf("not allowed");
            }

            break;
        case DOWN:
            // move 0 & 3

            if(isEmpty(blocks[0].x-1, blocks[0].y-2) &&
                isEmpty(blocks[1].x, blocks[1].y-1) &&
                isEmpty(blocks[3].x-1, blocks[3].y+1)
            ){
                blocks[3].x--;
                blocks[3].y++;
                blocks[1].y--;
                blocks[0].y -= 2;
                blocks[0].x--;
                facing = RIGHT;
            } else {
                printf("not allowed");
            }

            break;
        case RIGHT:
            // move 0 & 1

            if(isEmpty(blocks[0].x-1, blocks[0].y+1) &&
                isEmpty(blocks[1].x-2, blocks[1].y) &&
                isEmpty(blocks[3].x+1, blocks[3].y+1)
            ){
                blocks[0].x--;
                blocks[0].y++;
                blocks[1].x -= 2;
                blocks[3].x++;
                blocks[3].y++;
                facing = UP;
            } else {
                printf("not allowed");
            }
            break;
    }
}

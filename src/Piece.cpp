#include "include/Piece.h"

Piece::Piece(int x, int y){
    blocks[0] = Block{x, y};
    blocks[1] = Block{x, y-1};
    blocks[2] = Block{x+1, y};
    blocks[3] = Block{x+1, y+1};

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

    Block *block = blocks;
    for(int i=0; i<4; i++){
        block->x += xMove;
        block->y += yMove;
        block++;
    }
}

void Piece::rotateCW(){
    Block pivot = blocks[2]; // PIVOT IS 2

    switch(facing){
        case UP:
            // move 0 & 1
            blocks[0].x = pivot.x;
            blocks[0].y = pivot.y-1;
            blocks[1].x = pivot.x+1;
            blocks[1].y = pivot.y-1;
            blocks[3].x = pivot.x-1;
            blocks[3].y = pivot.y;
            facing = RIGHT;

            break;
        case RIGHT:
            blocks[0].x = pivot.x+1;
            blocks[0].y = pivot.y+1;
            blocks[1].x = pivot.x+1;
            blocks[1].y = pivot.y;
            blocks[3].x = pivot.x;
            blocks[3].y = pivot.y-1;
            facing = DOWN;
            break;
        case DOWN:
            blocks[0].x -= 2;
            blocks[3].y += 2;
            facing = LEFT;
            break;
        case LEFT:
            blocks[0].y--;
            blocks[1].x -= 2;
            blocks[1].y--;
            facing = UP;
            break;
    }
}

// TODO: move this into implementations of abstract class (whatever that is in c++)
void Piece::rotateCCW(){

    switch(facing){
        case UP:
            // move 0 & 1
            blocks[0].y++;
            blocks[1].x += 2;
            blocks[1].y += 1;
            facing = LEFT;

            break;
        case LEFT:
            // move 0 & 3
            blocks[0].x += 2;
            blocks[3].y -= 2;
            facing = DOWN;

            break;
        case DOWN:
            // move 0 & 3
            // blocks[0].x -= 2;
            // blocks[3].y += 2;
            // facing = LEFT;

            blocks[3].x--;
            blocks[3].y++;
            blocks[1].y--;
            blocks[0].y -= 2;
            blocks[0].x--;
            facing = RIGHT;

            break;
        case RIGHT:
            // move 0 & 1
            blocks[0].x--;
            blocks[0].y++;
            blocks[1].x -= 2;
            blocks[3].x++;
            blocks[3].y++;
            facing = UP;
            break;
    }
}

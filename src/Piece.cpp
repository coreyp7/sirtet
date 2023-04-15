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

void Piece::rotateCCW(){
    switch(facing){
        case UP:
            // move 0 & 1

            if((blocks[0].y+1 < gridHeight) && 
            (blocks[1].y+1 < gridHeight) && 
            (blocks[1].x+2 < gridWidth)){
                blocks[0].y++;
                blocks[1].x += 2;
                blocks[1].y += 1;
                facing = RIGHT;
            } else { // rotate it backwards, as if we were facing DOWN
                blocks[0].x--;
                blocks[0].y++;
                blocks[1].x++;
                blocks[1].y++;
                blocks[2].x--;
                blocks[3].x--;
                facing = LEFT;
            }

            break;
        case RIGHT:
            // move 0 & 3
            blocks[0].x += 2;
            blocks[3].y -= 2;

            facing = DOWN;
            break;
        case DOWN:
            // move 0 & 3
            if((blocks[0].x - 2 < 0) && (blocks[3].y + 2 > gridHeight)){
                blocks[0].x -= 2;
                blocks[3].y += 2;
                facing = LEFT;
            } else { // rotate it fowards, as if we were facing UP
                blocks[0].x++;
                blocks[1].x++;
                blocks[2].x++;
                blocks[3].x++;
                blocks[3].y += 2;
                facing = RIGHT;
            }
            break;
        case LEFT:
            // move 0 & 1
            blocks[0].y--;
            blocks[1].x -= 2;
            blocks[1].y -= 1;
            facing = UP;
            break;
    }
}

// TODO: move this into implementations of abstract class (whatever that is in c++)
void Piece::rotateCW(){

    switch(facing){
        case UP:
            // move 0 & 1
            blocks[0].y++;
            blocks[1].x += 2;
            blocks[1].y += 1;
            facing = RIGHT;

            if(blocks[1].x >= gridWidth){ // against right wall
                blocks[0].x--;
                blocks[1].x--;
                blocks[2].x--;
                blocks[3].x--;
                facing = LEFT;
            }

            break;
        case RIGHT:
            // move 0 & 3
            blocks[0].x += 2;
            blocks[3].y -= 2;

            facing = DOWN;
            break;
        case DOWN:
            // move 0 & 3
            blocks[0].x -= 2;
            blocks[3].y += 2;
            facing = LEFT;
            
            if(blocks[0].x < 0){ // against left wall
                blocks[0].x++;
                blocks[1].x++;
                blocks[2].x++;
                blocks[3].x++;
                facing = RIGHT;
            }

            break;
        case LEFT:
            // move 0 & 1
            blocks[0].y--;
            blocks[1].x -= 2;
            blocks[1].y -= 1;
            facing = UP;
            break;
    }
}

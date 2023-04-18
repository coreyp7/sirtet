#include "include/Block.h"

Block::Block(int x, int y){
    this->x = x;
    this->y = y;
}

Block::Block(){
    
}

void Block::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}
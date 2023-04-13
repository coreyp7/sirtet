#include "include/Piece.h"

Piece::Piece(SDL_Renderer *renderer, SDL_Color color, SDL_Rect (*grid)[]){
    this->renderer = renderer;
    this->color = color;
    this->grid = grid;

    x = 0;
    y = 1;

}

void Piece::render(){

}

SDL_Rect* getTileRect(int x, int y){
    if((x >= GRID_WIDTH) || (y >= GRID_HEIGHT)){
        return NULL;
    }

    int rowStart = y * GRID_WIDTH;
    return &grid[rowStart + x];
}
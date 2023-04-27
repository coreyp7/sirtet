#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "include/Text.h"
#include "include/constants.h"
#include "include/Globals.h"

// Viewport for entire window
const SDL_Rect windowViewport = {
    0, 0, WINDOW_WIDTH, WINDOW_HEIGHT
};

// Viewport specifically for the tetris grid.
const SDL_Rect gridViewport = {
        ( WINDOW_WIDTH - (GRID_WIDTH*TILE_SIZE) )/2,
        WINDOW_HEIGHT - (GRID_HEIGHT*TILE_SIZE) - 50,
        GRID_WIDTH*TILE_SIZE, GRID_HEIGHT*TILE_SIZE
};

const SDL_Rect queueViewport = {
    gridViewport.x + gridViewport.w,
    gridViewport.y+150,
    100, //(4*10)*5
    300
};

// For held piece
const SDL_Rect heldViewport = {
    gridViewport.x - 70,
    gridViewport.y + 205,
    5*10, 4*10
};

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern TTF_Font* globalFont;

extern SDL_Texture* spriteSheet;
extern SDL_Rect blockTextures[7];

extern SDL_Texture* bg;
extern SDL_Texture* greyPng;

void render();
void renderTetrisGrid();

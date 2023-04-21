// #include <SDL.h>
// #include <SDL_image.h>
// #include <SDL_ttf.h>
// #include <SDL_mixer.h>
// #include <stdio.h>
#pragma once
#include <include/Tile.h>
#include <stddef.h>
#include "array"

const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;

/* Initializes all of the SDL stuff needed. */
// int init(SDL_Window* window, SDL_Renderer *renderer, int windowWidth, int windowHeight);
// Get pointer to rect at position specified.
// (Top left going down)
// Returns NULL if the requested grid position is invalid.
Tile* getTile(int x, int y, std::array<Tile, GRID_WIDTH*GRID_HEIGHT> *grid);

typedef struct {
    int x;
    int y;
} Pair;
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "include/Piece.h"
#include <stdio.h>
#include "include/render.h"
#include "include/constants.h"
#include "include/Globals.h"
#include <vector>
#include "include/Tile.h"

// Just a wrapper for SDL_GetTicks, so GameState can get current time.
Uint32 getTime();
int init();
int loadAssets();
void fillGrid();
Tile* getTile(int x, int y);

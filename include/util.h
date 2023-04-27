#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "include/render.h"
#include "include/constants.h"
#include "include/Globals.h"
#include <vector>
#include "include/Piece.h"
#include "include/Tile.h"

void handleInput(std::vector<SDL_Keycode> keysPressed, Piece *piece);
int init();
int loadAssets();
void fillGrid();

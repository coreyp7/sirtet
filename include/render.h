#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "include/Text.h"
#include "include/constants.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern TTF_Font* globalFont;

extern SDL_Texture* spriteSheet;
extern SDL_Rect blockTextures[7];

extern SDL_Texture* bg;
extern SDL_Texture* greyPng;

void render();
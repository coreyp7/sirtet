#include "include/render.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

TTF_Font* globalFont = NULL;

SDL_Texture* spriteSheet = NULL;
SDL_Rect blockTextures[7];

SDL_Texture* bg = NULL;
SDL_Texture* greyPng = NULL;
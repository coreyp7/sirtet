#include "include/render.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

TTF_Font* globalFont = NULL;

SDL_Texture* spriteSheet = NULL;
SDL_Rect blockTextures[7];

SDL_Texture* bg = NULL;
SDL_Texture* greyPng = NULL;

void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    Text exampleText = Text(renderer, globalFont, constants::SDL_COLOR_WHITE);
    exampleText.changeText("Example text");
    exampleText.render(100, 100);
    SDL_RenderPresent(renderer);
}
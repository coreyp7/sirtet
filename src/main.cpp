#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

/* Project includes */
#include "include/util.h"

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

SDL_Window *window;
SDL_Renderer *renderer;


void gameLoop(){
    bool quit = false;

    SDL_Event event;
    

    while(!quit){

        while(SDL_PollEvent(&event) != 0){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
    }
    
}

void cleanup(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]){
    init(window, renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    gameLoop();

    cleanup();
    // TODO: cleanup function before closing
    return 0;
}
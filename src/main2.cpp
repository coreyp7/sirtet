#include "include/util.h"
#include "include/render.h"
#include "include/constants.h"

int main(int argc, char* args[]){
    int good = init();
    if(good<0){
        printf("not good %i", good);
        return -1;
    }
    printf("Hello world!");

    bool quit = false;
    SDL_Event event;
    std::vector<SDL_Keycode> keysPressed;

    fillGrid(); // fill grid with Tile objects

    while(!quit){
        // event loop
        while(SDL_PollEvent(&event) != 0){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    keysPressed.push_back(event.key.keysym.sym);
                    break;
            }
        }

        // if(!keysPressed.empty()){
        //     handleInput(keysPressed, currentPiece);
        //     keysPressed.clear();
        // }

        render();
    }

    // Testing
    // fillGrid();

    // gameLoop();

    // cleanup();
    // TODO: cleanup function before closing
    return 0;
}

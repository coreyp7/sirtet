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

    // Testing
    // fillGrid();

    // gameLoop();

    // cleanup();
    // TODO: cleanup function before closing
    return 0;
}

#include <SDL.h>

class Piece {
    public:
        Piece(SDL_Renderer *renderer, SDL_Color color, SDL_Rect (*grid)[]);
        void render();

    private:
        SDL_Renderer *renderer;
        SDL_Color color; // color of piece
        SDL_Rect (*grid)[];

        int x, y;
};
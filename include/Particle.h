#include <SDL.h>
class Particle {
    public:
        int x, y;
        int opacity;
        SDL_Color color;

        Particle(int x, int y);
        ~Particle();

        void simulate(); // TODO: pass dt to this
        // make sure to be in correct viewport
        void render(SDL_Renderer* renderer); 
};
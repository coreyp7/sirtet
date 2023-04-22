#include "include/Particle.h"

Particle::Particle(int x, int y){
    this->x = x;
    this->y = y;
    opacity = 255;
}

Particle::~Particle(){

}

void Particle::simulate(){
    opacity--;
}

void Particle::render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, opacity);
    SDL_RenderDrawPoint(renderer, x, y);
}
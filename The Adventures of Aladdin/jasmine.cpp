#include "Jasmine.hpp"
#include <iostream>

using namespace std;

Jasmine* Jasmine::instance = 0;

Jasmine::Jasmine(SDL_Texture *asst):assets(asst)
{
    mover = {720, 500, 75, 100}; //720
    MoveCount = 0;
}


void Jasmine::Move(bool flag4, SDL_RendererFlip flip)
{
    if (flag4==true)
    {
        if (flip==SDL_FLIP_NONE)
        {
            mover.x -=20; //move across the screen
            if (MoveCount==0)
            {
                JasmineSrc = {5, 53, 31, 57};
            }
            else if (MoveCount==1)
            {
                JasmineSrc = {34, 56, 32, 54};
            }
            else if (MoveCount==2)
            {
                JasmineSrc = {64, 52, 29, 57};
            }
            else if (MoveCount==3)
            {
                JasmineSrc = {93, 55, 31, 55};
                MoveCount=-1;
            }
            MoveCount++;
        }
        else if (flip==SDL_FLIP_HORIZONTAL)
        {
            mover.x+=20;
        }
        
    }
}

void Jasmine::draw(SDL_Renderer* gRenderer)
{
    SDL_RenderCopyEx(gRenderer, assets, &JasmineSrc, &mover, 0, NULL, SDL_FLIP_HORIZONTAL);
}

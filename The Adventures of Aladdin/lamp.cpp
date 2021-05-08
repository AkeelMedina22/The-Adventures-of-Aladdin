#include "lamp.hpp"
#include <iostream>

Lamp::Lamp(SDL_Texture *asst):assets(asst)
{
    mover = {950, 540, 35, 35};
    //health =1;
}

void Lamp::draw(SDL_Renderer* gRenderer)
{
    SDL_RenderCopy(gRenderer, assets, &src, &mover); //crashes at this line
    //SDL_RenderCopyEx(gRenderer, assets, &src, &mover, 0, NULL, SDL_FLIP_NONE);
}

void Lamp::createOutFile(std::ostream &myfile)
{
    myfile << name() << std::endl;
    myfile << mover.x <<std::endl;
}

void Lamp::move(SDL_RendererFlip flip, bool flag3)
{
    if (flag3==true) //when key is indeed pressed
    {
        if (flip==SDL_FLIP_NONE)
        {
            mover.x-=20;
        }
        else if (flip==SDL_FLIP_HORIZONTAL)
        {
            mover.x+=20;
        }
    }
}

char Lamp::name()
{
    return 'L';
}

void Lamp::setMove(int x)
{
    mover.x = x;
}
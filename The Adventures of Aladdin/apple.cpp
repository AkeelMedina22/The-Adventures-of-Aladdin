#include "apple.hpp"
#include <iostream>

Apple::Apple(SDL_Texture *asst):assets(asst)
{
    mover = {900, 540, 35, 35};
    //health =1;
}

void Apple::draw(SDL_Renderer* gRenderer)
{
    SDL_RenderCopy(gRenderer, assets, &src, &mover); //crashes at this line
    //SDL_RenderCopyEx(gRenderer, assets, &src, &mover, 0, NULL, SDL_FLIP_NONE);
}

void Apple::move(SDL_RendererFlip flip, bool flag3)
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

char Apple::name()
{
    return 'P';
}

void Apple::setMove(int x)
{
    mover.x = x;
}

void Apple::createOutFile(std::ostream &myfile)
{
    myfile << name() << std::endl;
    myfile << mover.x <<std::endl;
}

#include "alien.hpp"
#include <iostream>

Alien::Alien(SDL_Texture *asst):assets(asst)
{
    mover = {740, 500, 75, 100}; //720
    MoveCount = 0;
    AttackCount = 0;
    hurtCount = 0;
    health = 7;
}

void Alien::draw(SDL_Renderer* gRenderer)
{
    SDL_RenderCopyEx(gRenderer, assets, &src, &mover, 0, NULL, SDL_FLIP_NONE);
}

void Alien::createOutFile(std::ostream &myfile)
{
    myfile << getType() << std::endl;
    myfile << health << std::endl;
    myfile << mover.x <<std::endl;
}

void Alien::emove(bool move, bool flag2)
{
    if (flag2 ==true)
    {
        if (move==true)
        {
            mover.x-=20;
        }

        if (MoveCount==0)
        {
            src = {335,48,133,132};
        }
        else if (MoveCount ==1)
        {
            src = {346, 237, 120, 130};
        }
        else if (MoveCount==2)
        {
            src = {491, 235, 118, 137};
        }
        else if (MoveCount ==3)
        {
            src = {629, 234, 130, 135};
        }
        else if (MoveCount==4)
        {
            src = {774, 241, 128, 127};
        }
        else if (MoveCount==5)
        {
            src = {924, 237, 118, 130};
        }
        else if (MoveCount==6)
        {
            src = {1072, 240, 115, 125};
            MoveCount = -1;
        }
        MoveCount++;
    }
    else
    {
        src = {335,48,133,132};
    }
}


void Alien::move(int mx, bool flag,bool flag2,SDL_RendererFlip flip) //flag boolean value which is set true when this enemy is created - will have to create new flag in game.cpp
{                                                                       //flag2 is variable that toggles true when left arrow key is down and false when it is up - use same flag2 from game.cpp
    if (flag == true)
    {
        int temp = mover.x - mx;
        if (temp>70)
        {
            emove(true, true);
        }
        else if (flip == SDL_FLIP_HORIZONTAL)
        {
            emove(false, flag2);
        }
    }
}

void Alien::attack()
{
    if (AttackCount==0)
    {
        src = {335,48,133,132};
        
    }
    else if (AttackCount==1)
    {
        src = {485, 609, 128, 125};
        
    }
    else if (AttackCount==2)
    {
        src = {770, 421, 128, 133};
        
    }
    else if (AttackCount==3)
    {
        src = {753, 609, 136, 126};
        
    }
    else if (AttackCount==4)
    {
        src = {898, 607, 133, 130};
        
    }
    else if (AttackCount==5)
    {
        src = {1039, 607, 146, 125};
    }
    else if (AttackCount ==6)
    {
        src = {335,48,133,132};
        AttackCount=-1;
    }
    AttackCount++;
}


void Alien::hurt()
{
    if (hurtCount==0)
    {
        src = {466, 791, 145, 129};
    }
    else if (hurtCount==1)
    {
        src = {615, 794, 141, 125};
    }
    else if (hurtCount==2)
    {
        src = {774, 793, 123, 127};
        hurtCount=-1;
    }
    hurtCount++;
}

char Alien::getType()
{
    return 'A';
}

void Alien::setHealthnMover(int helth, int xmov)
{
    health = helth;
    mover.x = xmov;
}

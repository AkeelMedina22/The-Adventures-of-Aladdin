#include "stickman.hpp"
#include <iostream>

StickMan::StickMan(SDL_Texture *asst):assets(asst)
{
    mover = {740, 500, 75, 100}; //720
    MoveCount = 0;
    AttackCount = 0;
    hurtCount = 0;
    health = 7;
}

void StickMan::draw(SDL_Renderer* gRenderer)
{
    SDL_RenderCopyEx(gRenderer, assets, &src, &mover, 0, NULL, SDL_FLIP_NONE);
}

void StickMan::createOutFile(std::ostream &myfile)
{
    myfile << getType() << std::endl;
    myfile << health << std::endl;
    myfile << mover.x <<std::endl;
}


void StickMan::emove(bool move, bool flag2)
{
    if (flag2 ==true)
    {
        if (move==true)
        {
            mover.x-=20;
        }

        if (MoveCount==0)
        {
            src = {0,171,57,66};
        }
        else if (MoveCount ==1)
        {
            src = {1, 4, 50, 76};
        }
        else if (MoveCount==2)
        {
            src = {47, 5, 54, 75};
        }
        else if (MoveCount ==3)
        {
            src = {103, 0, 58, 81};
        }
        else if (MoveCount==4)
        {
            src = {162, 0, 51, 83};
        }
        else if (MoveCount==5)
        {
            src = {207, 0, 47, 79};
        }
        else if (MoveCount==6)
        {
            src = {253, 1, 52, 80};
        }
        else if (MoveCount==7)
        {
            src = {301, 1, 61, 78};
        }
        else if (MoveCount==8)
        {
            src = {359, 6, 44, 77};
            MoveCount = -1;
        }
        MoveCount++;
    }
    else
    {
        src = {0,171,57,66};
    }
}


void StickMan::move(int mx, bool flag,bool flag2,SDL_RendererFlip flip) //flag boolean value which is set true when this enemy is created - will have to create new flag in game.cpp
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

void StickMan::attack(SDL_Texture* gTexture, SDL_Rect bgSRC)
{
    if (AttackCount==0)
    {
        src = {0,171,57,66};
        
    }
    else if (AttackCount==1)
    {
        src = {1, 77, 50, 87};
        
    }
    else if (AttackCount==2)
    {
        src = {47, 86, 57, 74};
        
    }
    else if (AttackCount==3)
    {
        src = {105, 92, 98, 68};
        
    }
    else if (AttackCount==4)
    {
        src = {202, 92, 91, 68};
        
    }
    else if (AttackCount==5)
    {
        src = {289, 90, 85, 69};
        //AttackCount=-1;
    }
    else if (AttackCount ==6)
    {
        src = {0,171,57,66};
        AttackCount=-1;
    }
    AttackCount++;
}


void StickMan::hurt()
{
    if (hurtCount==0)
    {
        src = {104, 155, 53, 84};
    }
    else if (hurtCount==1)
    {
        src = {158, 158, 47, 79};
    }
    else if (hurtCount==2)
    {
        src = {209, 162, 50, 72};
        hurtCount=-1;
    }
    hurtCount++;
}

char StickMan::getType()
{
    return 'S';
}

void StickMan::setHealthnMover(int helth, int xmov)
{
    health = helth;
    mover.x = xmov;
}



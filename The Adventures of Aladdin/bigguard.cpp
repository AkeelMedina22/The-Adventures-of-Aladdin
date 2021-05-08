#include "bigguard.hpp"
#include <iostream>

BigGuard::BigGuard(SDL_Texture *asst):assets(asst)
{
    mover = {740, 500, 75, 100}; //720
    MoveCount = 0;
    AttackCount = 0;
    hurtCount = 0;
    health = 7;
}


void BigGuard::draw(SDL_Renderer* gRenderer)
{
    SDL_RenderCopyEx(gRenderer, assets, &src, &mover, 0, NULL, SDL_FLIP_NONE);
}

void BigGuard::emove(bool move, bool flag2)
{
    if (flag2 ==true)
    {
        if (move==true)
        {
            mover.x-=20;
        }

        if (MoveCount==0)
        {
            src = {1, 251, 51, 60};
        }
        else if (MoveCount ==1)
        {
            src = {51, 248, 59, 63};
        }
        else if (MoveCount==2)
        {
            src = {107, 250, 64, 62};
        }
        else if (MoveCount ==3)
        {
            src = {170, 248, 61, 64};
        }
        else if (MoveCount==4)
        {
            src = {227, 254, 54, 56};
        }
        else if (MoveCount==5)
        {
            src = {282, 251, 51, 61};
        }
        else if (MoveCount==6)
        {
            src = {328, 247, 53, 67};
        }
        else if (MoveCount==7)
        {
            src = {380, 248, 54, 65};
            MoveCount = -1;
        }
        MoveCount++;
    }
    else
    {
        src = {1, 251, 51, 60};
    }
}




void BigGuard::move(int mx, bool flag,bool flag2,SDL_RendererFlip flip)
{
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

void BigGuard::attack(SDL_Texture* gTexture, SDL_Rect bgSRC)
{
    if (AttackCount==0)
    {
        src = {0,252,53,59};
        
    }
    else if (AttackCount==1)
    {
        src = {1, 442, 51, 69};
        
    }
    else if (AttackCount==2)
    {
        src = {52, 432, 55, 80};
        
    }
    else if (AttackCount==3)
    {
        src = {108, 435, 63, 79};
        
    }
    else if (AttackCount==4)
    {
        src = {176, 445, 119, 66};
        
    }
    else if (AttackCount==5)
    {
        src = {301, 432, 92, 80};
        //AttackCount=-1;
    }
    else if (AttackCount ==6)
    {
        src = {0,252,53,59};
        AttackCount=-1;
    }
    AttackCount++;
}

void BigGuard::hurt()
{
    if (hurtCount==0)
    {
        src = {65, 514, 71, 78};
    }
    else if (hurtCount==1)
    {
        src = {135, 522, 73, 68};
    }
    else if (hurtCount==2)
    {
        src = {206, 514, 80, 77};
        hurtCount=-1;
    }
    hurtCount++;
}
        
char BigGuard::getType()
{
    return 'B';
}

void BigGuard::setHealthnMover(int helth, int xmov)
{
    health = helth;
    mover.x = xmov;
}

void BigGuard::createOutFile(std::ostream &myfile)
{
    myfile << getType() << std::endl;
    myfile << health << std::endl;
    myfile << mover.x <<std::endl;
}


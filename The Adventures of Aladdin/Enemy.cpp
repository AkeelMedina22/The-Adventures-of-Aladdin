#include "Enemy.hpp"
#include<iostream>

using namespace std;

Enemy::Enemy(SDL_Texture* asst)
{
}


void Enemy::draw(SDL_Renderer* gRenderer)
{
    
}

void Enemy::move(int mx, bool flag,bool flag2,SDL_RendererFlip flip)
{

}

void Enemy::attack(SDL_Texture* gTexture, SDL_Rect bgSRC) //virtual attack function
{

}

void Enemy::hurt()
{
    
}

char Enemy::getType()
{

}

void Enemy::setHealthnMover(int helth, int xmov)
{

}

void Enemy::reduceHealth(char ch)
{
    if (ch == 'b') //basic attack -1 hit
    {
        health--; //reduce health by 1 on every hit
    }
    else if (ch == 'a') //advanced attack -3 hit
    {
        health = health -3;
    }
    if (health>0)
    {
        cout<<"Health is now: "<<health<<endl;
    }
    else
    {
        cout<<"Enemy is dead!"<<endl;
    }
}


void Enemy::checkCollison(SDL_Rect a, SDL_Rect b, SDL_RendererFlip flip, char ch)
{
    SDL_bool collision = SDL_HasIntersection(&a, &b);

    if (collision)
    {
        if ((b.x-a.x)<0) //enemy is on left side of Player
        {
            if (flip == SDL_FLIP_HORIZONTAL) //player is also facing left - thus attacking enemy from behind
            {
                reduceHealth(ch);
            }
        }
        else if ((b.x-a.x)>=0) //enemy is on right of Player
        {
            if (flip==SDL_FLIP_NONE) //player is also facing right - thus attacking enemy head on
            {
                reduceHealth(ch);
            }
        }	
    }
}

void Enemy::createOutFile(std::ostream &myfile)
{
    
}

bool Enemy::operator <= (int temp) //temp is a constant number 0
{
    if (health<=temp)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

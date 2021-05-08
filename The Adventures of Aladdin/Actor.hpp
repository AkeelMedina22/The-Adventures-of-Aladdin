//the class from which all characters inherit from

#include <SDL.h>
#include <fstream>
#pragma once
/**
 * \brief Parent class from which all Enemies, Player and Jasmine inherit from.
 */
class Actor
{
    protected:
    SDL_Rect mover;
    SDL_Renderer *gRenderer;
    SDL_Renderer *assests;
    int health;
    public:
    Actor(SDL_Texture*);
    Actor(){}
    void draw(SDL_Renderer*);
    SDL_Rect getMover(){return mover;}
    int getHealth(){return health;}
    void setHealth(){health++;};
};
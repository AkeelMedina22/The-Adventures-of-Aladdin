#pragma once
#include "Actor.hpp"

/**
 * \brief This class provides the move and animation functionality for the Jasmine character. It inherits from the Actor class.
 * This class is implemented using Singleton Design Pattern. 
 * MoveCount is tied to the move animation of the character. 
 */ 
class Jasmine: public Actor
{
    SDL_Texture *assets; //the textures that we'll also later pass onto the pigeon class
    SDL_Rect JasmineSrc = {7,116,27,58};
    int MoveCount;
    static Jasmine *instance;
public: 
    static Jasmine *getInstance(SDL_Texture *Jassets) {
      if (instance == 0)
      {
          instance = new Jasmine(Jassets);
          return instance;
      } 
   }
    /**
     * This is the constructor for the Jasmine class.
     * \param SDL_Texture* this provides the asset sheet from game.cpp. 
     */ 
    Jasmine(SDL_Texture *asst); 
    /**
     * This function calls the move animation of the Jasmine character.
     * \param flag4 this boolean variable is tied to Player movement. It is toggled so as to allow movement and animation when Player is moving towards the right.
     * \param flip provides the orientation of the Player. 
     */
    void Move(bool flag4, SDL_RendererFlip flip);
    /**
     * This function draws the Jasmine character on the screen.
     * \param SDL_Renderer* is the window renderer.
     */
    void draw(SDL_Renderer* gRenderer);
}; 


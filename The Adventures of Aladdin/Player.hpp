#pragma once
#include "Actor.hpp"
#include <sstream>
#include <fstream>
#include <istream>
#include <string>

/**
 * \brief This is the Player class (i.e. Aladdin). This class is implemented using Singleton Design Pattern. 
 * MoveCount is an integer tied to the movement animation of the Player.
 * SwordCount is an integer tied to the basic sword attack animation of the Player.
 * AdSword is an integer tied the advanced sword attack animation of the Player.
 * flip is a boolean variable which houses the orientation of the Player which is of type SDL_RendererFlip..
 * hurtCount is an integer tied to the hurt animation of the Player.
 * celebCount is an integer tied to the end game animation of the Player.
 */
class Player: public Actor
{
    SDL_Texture *assets; //the textures that we'll also later pass onto the pigeon class
    SDL_Rect PlayerSrc = {3,1219,58,62};
    int MoveCount;
    int SwordCount;
    int AdSword;
    bool flip;
    int hurtCount;
    int celebCount;
    static Player *instance;
public:
    static Player *getInstance(SDL_Texture *assets) {
      if (instance == 0)
      {
          instance = new Player(assets);
          return instance;
      } 
    }
    /**
     * This is the constructor for the Player class.
     * \param SDL_Texture* this provides the asset sheet from game.cpp. 
     */ 
    Player(SDL_Texture *asst);
    /**
     * This function is for the movement of the Player object.
     * \param move is a boolean that denotes whether or not the Player is actually moving which is boolean.
     * \param x is an integer used to move the background to help in creating a scrollable background that is a integer.
     * \param px is the integer distance of the Player with respect to the starting point that is a integer
     * \param flip provides the orientation of the Player which is of type SDL_RendererFlip.
     */ 
    void HorizontalMove(bool move, int &x, int &px, SDL_RendererFlip flip); //this function causes the animations.
    /**
     * This function handles the basic sword animation.
     */
    void BasicSword();
    /**
     * This function handles the advanced sword animation.
     */
    void AdvancedSword();
    /**
     * This function handles the hurt animation.
     */
    void hurt();
    /**
     * This function draws the Player character on the screen.
     * \param SDL_Renderer* is the window renderer.
     * \param flip gives the Player's orientation which is of type SDL_RendererFlip.
     */
    void draw(SDL_Renderer* gRenderer, SDL_RendererFlip flip);
    /**
     * This function reduces Player health.
     */
    void reduceHealth();
    /**
     * This function handles the end game animation.
     */
    void celebration();

    void stateReset(); /**< resets player stats when there is a new game */
    void stateLoad();/**< loads all the players stats from file to member variables */
    void stateWrite();/**< writes all player stats to game file upon exit */
    /**
     * This is the increment operator overloaded. This is tied to the increment of Player health.
     */
    void operator ++();
    /**
     * This is the decrement operator overloaded. This is tied to the decrement of Player health.
     */
    void operator --();
    /**
     * This is the assignment operator overloaded. This is tied to gamebar management of Player health.
     */
    void operator = (int &applesLeft);
}; 
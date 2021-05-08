#pragma once
#include "Actor.hpp"

/**
 * \brief This is the Parent class to generate the enemies. This class further inherits from the Actor Class. 
 */
class Enemy: public Actor
{
    SDL_Texture* assets;
public:
    /**
    * This is the constructor for the Enemy class.
    * \param SDL_Texture* which is basically the asset file passed from the game.cpp.
    */
    Enemy(SDL_Texture* asst);
    /**
     * This is the default constructor for the Enemy class that does not take any arguments 
     */
    Enemy(){};
    /**
    * This virtual draw function renders the Enemy object on the screen.
    * \param SDL_Renderer*  
    */
    virtual void draw(SDL_Renderer* gRenderer);
    /**
     *This virtual function determines the static or movable nature of the Enemy object and thus appropiately plays the respective move animation. 
     * \param mx this is the integer x value of the Player's mover so as to determine the distance between the Enemy and Player and thus force Enemy movement towards the left.
     * \param flag boolean value which is set true when this enemy is created.
     * \param flag2 variable that toggles true when left arrow key is down and false when it is up.
     * \param flip denotes the orientation of the Player which is of type SDL_RendererFlip.
     */
    virtual void move(int mx, bool flag,bool flag2,SDL_RendererFlip flip);
    /**
     * This virtual function cycles through the attack animation of the Enemy.
     */
    virtual void attack(SDL_Texture* gTexture, SDL_Rect bgSRC);
    /**
     * This virtual function cycles through the death animation of the Enemy. 
     */
    virtual void hurt();
    /**
     * This virtual function returns the type of Enemy that it is.  
     */
    virtual char getType();
    /**
     * This virtual function sets the Enemy's health and position when loading the game from the save file.
     * \parm helth is the passed health integer value read from the save file.
     * \param xmov is the passed integer x-coordinate read from the save file.
     */
    virtual void setHealthnMover(int helth, int xmov);
    /**
     * This function reduces the health of the Enemy by a certain amount depending upon the type of attack recieved.
     * \param ch denotes a one character signifier as to the attack recieved. 
     */
    void reduceHealth(char ch);
    /**
     * This function checks for collision between the Enemy and the Player. If true reduceHealth is called.
     * \param a is the SDL_Rect mover for the Player.
     * \param b is the SDL_Rect mover for the Enemy.
     * \param flip denotes the orientation of the Player which is of type SDL_RendererFlip.
     * \param ch is a character that denotes the attack performed by the Player. 
     */
    void checkCollison(SDL_Rect a, SDL_Rect b, SDL_RendererFlip flip, char ch);
    /**
     * This is the less than or equal to operator overloaded.
     * \param temp is a constant integer that the Enemy is compared with in the context of its health value. 
     */
    bool operator <= (int temp);
    /**
     * This virtual function writes the type, health value and x-coordinate to our save file. 
     * \param myfile is the ostream object passed by reference from game.cpp when creating the save file.
     */
    virtual void createOutFile(std::ostream &myfile);
};
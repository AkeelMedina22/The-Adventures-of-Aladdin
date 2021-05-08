#pragma once
#include "Enemy.hpp"

/**
 * \brief This class inherits from the Enemy class. It is one of the three antagonists of the game.
 * MoveCount is the integer animation count tied to the movemnet of the StickMan.
 * AttackCount is the integer animation count tied to the attack sequence of the StickMan.
 * hurtCount is the integer animation count tied to the sequence when the StickMan is defeated.     
 */
class StickMan: public Enemy
{
    SDL_Texture *assets; //the textures that we'll also later pass onto the pigeon class
    SDL_Rect src = {0,171,57,66};
    int MoveCount;
    int AttackCount;
    int hurtCount;
public:
    /**
    * This is the constructor for the StickMan class.
    * \param SDL_Texture* which is basically the asset file passed from the game.cpp.
    */
    StickMan(SDL_Texture *asst); 
    /**
    * This draw function renders the StickMan object on the screen.
    * \param SDL_Renderer*  
    */
    void draw(SDL_Renderer* gRenderer);
    /**
    * This function cycles through the move animation of the StickMan.
    * \param move this is a boolean flag which toggles the x direction movement of the object on the screen.
    * \parm flag2 is a boolean flag which toggles whether or not the animation must play or not.
    */
    void emove(bool move, bool flag2);
    /**
     *This function determines the static or movable nature of the StickMan object and thus appropiately plays the respective move animation called through emove. 
     * \param mx this is the integer x value of the Player's mover so as to determine the distance between the StickMan and Player and thus force StickMan movement towards the left.
     * \param flag boolean value which is set true when this enemy is created.
     * \param flag2 is a boolean variable that toggles true when left arrow key is down and false when it is up.
     * \param flip denotes the orientation of the Player and this is of type SDL_RendererFlip. 
     */
    void move(int mx, bool flag,bool flag2,SDL_RendererFlip flip);
    /**
     * This function cycles through the attack animation of the StickMan. Cycling is done through AttackCount.
     * \param bgSRC is an SDL_Rect which provides background co-ordinates for rendering of scene during Attack.
     */
    void attack(SDL_Texture* gTexture, SDL_Rect bgSRC);
    /**
     * This function cycles through the death animation of the StickMan. Cycling is done through hurtCount. 
     */
    void hurt();
    /**
     * This function returns the type of Enemy that it is. In this case a StickMan  
     */
    char getType();
    /**
     * This function sets the StickMan's health and position when loading the game from the save file.
     * \parm helth is the passed health integer value read from the save file.
     * \param xmov is the passed integer x-coordinate read from the save file.
     */
    void setHealthnMover(int helth, int xmov);
    /**
     * This functions writes the type, health value and x-coordinate to our save file.
     * \param myfile is the ostream object passed by reference from game.cpp when creating the save file.
     */
    void createOutFile(std::ostream &myfile);
}; 


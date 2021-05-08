#pragma once
#include "Enemy.hpp"
/**
 * \brief This class inherits from the Enemy class. It is one of the three antagonists of the game.
 * MoveCount is the integer animation count tied to the movemnet of the BigGuard.
 * AttackCount is the integer animation count tied to the attack sequence of the BigGuard.
 * hurtCount is the  integer animation count tied to the sequence when the BigGuard is defeated.     
 */
class BigGuard: public Enemy
{
    SDL_Texture *assets; 
    SDL_Rect src = {0,252,53,59};
    int MoveCount;
    int AttackCount;
    int hurtCount;
public:
    /**
    * This is the constructor for the BigGuard class.
    * \param SDL_Texture* which is basically the asset file passed from the game.cpp.
    */
    BigGuard(SDL_Texture *asst); 
    /**
    * This draw function renders the BigGuard object on the screen.
    * \param SDL_Renderer*  
    */
    void draw(SDL_Renderer* gRenderer);
    /**
    * This function cycles through the move animation of the BigGuard.
    * \param move this is a boolean flag which toggles the x direction movement of the object on the screen.
    * \parm flag2 is a boolean flag which toggles whether or not the animation must play or not.
    */
    void emove(bool move, bool flag2);
    /**
     *This function determines the static or movable nature of the BigGuard object and thus appropiately plays the respective move animation called through emove. 
     * \param mx this is the integer x value of the Player's mover so as to determine the distance between the BigGuard and Player and thus force BigGuard movement towards the left.
     * \param flag boolean value which is set true when this enemy is created.
     * \param flag2 variable that toggles true when left arrow key is down and false when it is up.
     * \param flip denotes the orientation of the Player and this of type SDL_RendererFlip.
     */
    void move(int mx, bool flag,bool flag2,SDL_RendererFlip flip);
    /**
     * This function cycles through the attack animation of the BigGuard. Cycling is done through AttackCount.
     */
    void attack(SDL_Texture* gTexture, SDL_Rect bgSRC);
    /**
     * This function cycles through the death animation of the BigGuard. Cycling is done through hurtCount. 
     * \param bgSRC is an SDL_Rect which provides background co-ordinates for rendering of scene during Attack.
     */
    void hurt();
    /**
     * This function returns the type of Enemy that it is. In this case a BigGuard  
     */
    char getType();
    /**
     * This function sets the BigGuard's health and position when loading the game from the save file.
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
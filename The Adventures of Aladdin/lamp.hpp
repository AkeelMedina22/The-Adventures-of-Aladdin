#pragma once
#include "obstacles.hpp"

/**
 * \brief This class inherits from the Obstalces class. It is one of the two static objects which interact with the Player. The specific function of this object is related to the points of the Player. 
 */
class Lamp: public Obstacles
{
    SDL_Texture *assets; 
    SDL_Rect src = {32, 951, 52, 29};
    int point;
public:
    /**
     * This is the constructor for the Lamp class.
     * \param SDL_Texture* which is basically the asset file passed from the game.cpp. 
     */
    Lamp(SDL_Texture *asst); 
    /**
    * This draw function renders the Lamp object on the screen.
    * \param SDL_Renderer*  
    */
    void draw(SDL_Renderer* gRenderer);
    /**
     * This function moves the Lamp object onto the screen when appropiate. When the Player is moving to the right the Lamp is reducing the x value. When player is moving to the left, we are increasing the x value.
     * \param flip provides the class with the orientation of the player which is of type SDL_RendererFlip..
     * \param flag3 is a boolean that is toggled true when Player is pressing the key down.  
     */
    void move(SDL_RendererFlip flip, bool flag3);
    /**
     * This function provides us with the specific type of Obstacle. In this case an Lamp. 
     */
    char name();
    /**
     * This function sets the integer x cooridinate of the Lamp when loading from save file. 
     */
    void setMove(int x);
    /**
     * This functions writes the type, integer health value and integer x-coordinate to our save file.
     * \param myfile is the ostream object passed by reference from game.cpp when creating the save file.
     */
    void createOutFile(std::ostream &myfile);
}; 


//the class from which all Obstacles inherit from

#include <SDL.h>
#include <fstream>
#pragma once
/**
 * \brief This is the Parent class to generate the obstacles. 
 */
class Obstacles
{
    protected:
    SDL_Rect mover;
    SDL_Renderer *gRenderer;
    SDL_Renderer *assets;
    public:
    /**
    * This is the constructor for the Obstacles class.
    * \param SDL_Texture* which is basically the asset file passed from the game.cpp.
    */
    Obstacles(SDL_Texture* asst);
    /**
     * This is the default constructor for the Obstacles class that does not take any arguments 
     */
    Obstacles(){}
    /**
    * This virtual draw function renders the Obstacles object on the screen.
    * \param SDL_Renderer*  
    */
    virtual void draw(SDL_Renderer*);
    /**
     * This function moves the Obstalces object onto the screen when appropiate. When the Player is moving to the right the Obstacle is reducing the x value. When player is moving to the left, we are increasing the x value.
     * \param flip provides the class with the orientation of the player which is of type SDL_RendererFlip..
     * \param flag3 is a boolean that is toggled true when Player is pressing the key down.  
     */
    virtual void move(SDL_RendererFlip flip, bool flag3);
    /**
     * This function returns the mover for the obstacle. 
     */
    SDL_Rect getMove();
    /**
     * This function returns the specific type of Obstacle. 
     */
    virtual char name();
    /**
     * This function sets the x cooridinate of the Obstacle when loading from save file. 
     */
    virtual void setMove(int x);
    /**
     * This functions writes the type, integer health value and integer x-coordinate to our save file.
     * \param myfile is the ostream object passed by reference from game.cpp when creating the save file.
     */
    virtual void createOutFile(std::ostream &myfile);
};
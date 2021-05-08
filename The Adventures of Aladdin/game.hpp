/*
Assignment was done in a group of 2:
Name: Fahad Shaikh (05452) and Akeel Ather Medina (05427)
Instructor: Dr. Akhlaque Ahmed
Course: CS224
Section: L2
*/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <limits>
#include <string>
#include <list>
#include "Enemy.hpp"
#include "Player.hpp"
#include "BigGuard.hpp"
#include "stickman.hpp"
#include "alien.hpp"
#include "jasmine.hpp"
#include "obstacles.hpp"
#include "apple.hpp"
#include "lamp.hpp"
#include "factoryEnemy.hpp"
#include "factoryObstacles.hpp"

using namespace std;

/**
 *  \brief This is the Game Class which runs the game and interacts with all the other classes.
 */
class Game
{
    //private scope:
private:
    //Screen dimension constants
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    SDL_Texture* gBackgroundTexture = NULL;
    //global reference to png image sheets
    SDL_Texture* assets=NULL;
    SDL_Texture* Eassets=NULL;
    SDL_Texture* Aassets=NULL; //alien spritesheet  
    SDL_Texture* Iassets=NULL;     // item spritesheet  
    SDL_Texture* Jassets=NULL;  
    Mix_Music *bgMusic = NULL;
    //the list where we store all the enemies as they are created at their specified moments (their pointers to be exact).
    list<Enemy*> enemys; 

    list<Obstacles*> items;

    list<Jasmine*> jasList;

    int applesLeft = 10;
    int points = 0;
    int bGuardCount = 0; //counter for preventing excess enemies from being formed (in particular the Big Guard)
	int smanCount = 0;
	int alienCount = 0;
    int jasCount = 0;

    SDL_Texture* gButtonSpriteSheetTexture1;
    SDL_Texture* gButtonSpriteSheetTexture2;
    SDL_Texture* gVolumeButtonTexture;
    SDL_Texture* gMuteButtonTexture;
    SDL_Texture* gQuitButtonTexture;
    SDL_Texture* gVictoryButtonTexture;
    SDL_Texture* gLoseButtonTexture;

    SDL_Rect g1 = {225, 150, 300, 100};
    SDL_Rect g2 = {225, 350, 300, 100};
    SDL_Rect g3 = {0, 0, 50, 50};
    SDL_Rect g4 = {225, 250, 300, 100};
    SDL_Rect g5 = {225, 20, 300, 350};
    SDL_Rect g6 = {225, 450, 300, 100};

    bool play;
    bool music;
    bool paused;
    bool victory;
    bool lose;
public:
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    /**
     * This functions houses a while loop wherein the game continously runs until the quit condition is not met.  
     */
    void run();
    /**
     * This function draws all the Enemies that are currently within the enemys list.
     * \param mx this provides the Player's  integer x coordinate.
     * \param flag is a boolean related to creation of the Enemies.
     * \param flag2 is a boolean that instigates Enemy move animations but depending upon the value toggles the actual movement across the screen.
     * \param flip provides the orientation of the Player which is of type SDL_RendererFlip.
     * \param flag3 is a boolean that is toggled true when the Player is pressing the move key down. This is related to Obstacles movement.
     */
    void drawAllObjects(int mx, bool flag,bool flag2,SDL_RendererFlip flip, bool flag3);
    /**
     * This function calls the attack fucntion for all the enemies present in the scene if a certain probability is met.
     * \param bgSrc provides SDL_Rect src rectangle for the background - this is to generate the scene when dealing with the attack animation.
     * \param Player* is a pointer to the Player object.
     * \param flip provides the orientation of the Player.
     * \param flag3 is toggled true when the Player is pressing the move key down. This is related to Obstacles movement.
     */
    void EnemyAttack(SDL_Rect bgSrc, Player* ptr, SDL_RendererFlip flip, bool flag3);
    /**
     * This function calls the attack function of the Player and decreases the health of the Enemy provided there is a collision.
     * \param Player*, this is the Player object's pointer.
     * \param flip provides the orientation of the Player which is of type SDL_RendererFlip.
     * \param ch is a character that provides the attack performed by the Player.
     * \param bgSRC provides SDL_Rect src rectangle for the background - this is to generate the scene when dealing with the attack animation.
     * \param flag3 is a boolean that is toggled true when the Player is pressing the move key down. This is related to Obstacles movement.
     */
    void playerAttack(Player* ptr, SDL_RendererFlip flip, char ch, SDL_Rect bgSRC, bool flag3);
    /**
     * This function is to relagate the fucntionality of the game bar at the top of the screen - the health and point meter.
     * \param SDL_Renderer* to render the apple and lamp sprites.
     * \param SDL_Texture* for the passing of the appropiate spritesheet.
     */
    void status(SDL_Renderer* gRenderer, SDL_Texture* assets);
    /**
     * This function draws all the Obstacles that are currently within the items list.
     * \param flip provides the orientation of the Player which is of type SDL_RendererFlip.
     * \param flag3 is a boolean that is toggled true when the Player is pressing the move key down. This is related to Obstacles movement.
     */
    void drawAllItems(SDL_RendererFlip flip, bool flag3);
    /**
     * This function draws the Jasmine character when she exists provided the required condition for her creation is met.
     * \param flag4 is a boolean related to the Move function of Jasmine so as to have her move across the screen with the animation only when the Player is moving to the right. 
     * \param flip provides the orientation of the Player which is of type SDL_RendererFlip.
     */
    void drawJas(bool flag4, SDL_RendererFlip flip);

    //! Checks mouse input on main menu screen
    /*!
      \param SDL_Event* e SDL Event pointer that tells us when the mouse is pressed.
      \param Player &p The player generated during game, in case of load game, this needs to be written to file.
      \param SDL_Rect &bgSRC this is the background mover that makes it scrollable. It needs to be reset, or read from file.
      \param int &px This is the players (ajlal pls help)
    */
    void mouseOnBackgroundButton(SDL_Event* e, Player &p, SDL_Rect &bgSRC, int &px, int &enyval, int& appleval, int& lampval); 

    //! Checks mouse input on pause screen
    /*!
      \param SDL_Event* e SDL Event pointer that tells us when the mouse is pressed.
      \param Player &p The player generated during game, in case of load game, this needs to be written to file.
      \param SDL_Rect &bgSRC this is the background mover that makes it scrollable. It needs to be reset, or read from file.
    */
    void mouseOnQuitButton(SDL_Event* e, Player &p, SDL_Rect &bgSRC);

    //! Checks mouse input on quit button on victory or lose screen 
    /*!
      \param SDL_Event* e SDL Event pointer that tells us when the mouse is pressed.
      \param Player &p The player generated during game, in case of load game, this needs to be written to file.
      \param SDL_Rect &bgSRC this is the background mover that makes it scrollable. It needs to be reset, or read from file.
      \param bool low this is to make clear this function is overloaded and is for victory screen, has no use
      \param int &px this is the players virtual position and needs to be reset
    */
    void mouseOnQuitButton(SDL_Event* e, Player &p, SDL_Rect &bgSRC, bool low, int& px);

    //! resets the game and deletes all objects
    /*!
      \param Player &p The player generated during game, in case of load game, this needs to be written to file.
      \param SDL_Rect &bgSRC this is the background mover that makes it scrollable. It needs to be reset, or read from file.
    */
    void gameReset(Player &p, SDL_Rect &bgSRC);

    //! loads from file upon the load game button press 
    /*!
      \param SDL_Rect &bgSRC this is the background mover that makes it scrollable. It needs to be reset, or read from file.r This is the SDL Rectangle that 
      \param int &points This is the variable holding the amount of points a player has, and when loading, it needs to be set.
    */
    void readBGFromFile(SDL_Rect &r, int &points);
    /**
     * This function checks for collisions of the Player with the respective objects - either health incremnet or score supplement.
     * \param Player*, this is the Player object's pointer.
     */ 

    
    void objectCollision(Player* ptr);
    /**
     * This function checks for collisions of the Player with Jasmine. If collision occurs then the end game scenario takes place.
     * \param Player*, this is the Player object's pointer.
     * \param bgSRC provides SDL_Rect src rectangle for the background - this is to generate the scene when dealing with the end game scenario.
     * \param flip provides the Player's orientation which is of type SDL_RendererFlip.
     */
    void JasmineCollision(Player* ptr, SDL_Rect &bgSRC, SDL_RendererFlip flip);
    /**
     * This function deletes all Enemies and Obstacles.
     * \param enemys is the list of type Enemy*. It houses all the enemies.
     * \param items is the list of type Obstacles*. It houses all the obstacles.
     */
    void deleteAllObjects(list<Enemy*> &enemys, list<Obstacles*> &items);
};


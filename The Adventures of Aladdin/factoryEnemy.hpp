#include "Enemy.hpp"
#include "bigguard.hpp"
#include "stickman.hpp"
#include "alien.hpp"

/**
 * \brief This class implements the Factory design pattern and returns a pointer of Enemy object depending upon the type passed in the constructor of this class.
 */
class FactoryEnemy
{
    Enemy* eny;

    public:
    /**
     * This constructor creates the Enemy object depending upon the type.
     * \param type is an integer variable to determine which Enemy object is to be produced. 
     * \param SDL_Texture* is the asset sheet passed from game.cpp.
     */
    FactoryEnemy(int type, SDL_Texture* asst);
    /**
     * This destructor is clearing the dynamically allocated memory for the objects. 
     */
    ~FactoryEnemy();
    /**
     * This function is just returning the pointer to the Enemy object once it is created. Return type is Enemy*.
     */
    Enemy* getEnemy();

};
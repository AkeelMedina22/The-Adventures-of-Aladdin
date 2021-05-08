#include "obstacles.hpp"
#include "apple.hpp"
#include "lamp.hpp"

/**
 * \brief This class implements the Factory design pattern and returns a pointer of Obstacles object depending upon the type passed in the constructor of this class.
 */
class FactoryObstacles
{
    Obstacles* obs;

    public:
    /**
     * This constructor creates the Obstacles object depending upon the type.
     * \param type is an integer variable to determine which Obstacles object is to be produced. 
     * \param SDL_Texture* is the asset sheet passed from game.cpp.
     */
    FactoryObstacles(int type, SDL_Texture* asst);
    /**
     * This destructor is clearing the dynamically allocated memory for the objects. 
     */
    ~FactoryObstacles();
    /**
     * This function is just returning the pointer to the Obstacles object once it is created. Return type is Obstacles*.
     */
    Obstacles* getObstacles();
};
#include "factoryObstacles.hpp"

FactoryObstacles::FactoryObstacles(int type, SDL_Texture* asst)
{
    if (type == 1)
    {
        obs = new Apple(asst);
    }
    else if (type == 2)
    {
        obs = new Lamp(asst);
    }
}


FactoryObstacles::~FactoryObstacles()
{
    if (obs)
    {
        delete[] obs;
        obs = NULL;
    }
}

Obstacles* FactoryObstacles::getObstacles()
{
    return obs;
}


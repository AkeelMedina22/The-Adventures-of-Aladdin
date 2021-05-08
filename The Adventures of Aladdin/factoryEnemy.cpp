#include "factoryEnemy.hpp"

FactoryEnemy::FactoryEnemy(int type, SDL_Texture* asst)
{
    if (type == 1)
    {
        eny = new BigGuard(asst);
    }
    else if (type == 2)
    {
        eny = new StickMan(asst);
    }
    else if (type == 3)
    {
        eny = new Alien(asst);
    }
}


FactoryEnemy::~FactoryEnemy()
{
    if (eny)
    {
        delete[] eny;
        eny = NULL;
    }
}

Enemy* FactoryEnemy::getEnemy()
{
    return eny;
}
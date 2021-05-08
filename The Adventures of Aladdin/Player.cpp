
#include "Player.hpp"
#include <iostream>

using namespace std;

Player* Player::instance = 0;

Player::Player(SDL_Texture *asst):assets(asst)
{
    mover = {300, 500, 75, 100};
    MoveCount = 0;
    SwordCount = 0;
    AdSword = 0;
    hurtCount = 0;
    flip = false;
    health = 10;
    celebCount = 0;
}



void Player::HorizontalMove(bool move, int& x, int& px, SDL_RendererFlip flip)
{
    if (x > 5750 - 1700)
    {
        x = 0;
    }

    if (flip == SDL_FLIP_NONE)
    {
        x+=20;
        px+=20;   // Player's virtual position changed.
    }
    else if(flip == SDL_FLIP_HORIZONTAL)
    {
        if (x > 20)
        {
            x-=20;
            px-=20;
        }
        
    }
    
    if (move == true) //is moving
    {
        if (MoveCount==0) //first
        {
            PlayerSrc = {61,1218,51,56};
        }
        else if (MoveCount==1) //second
        {
            PlayerSrc = {112, 1215, 53, 63};
        }
        else if (MoveCount==2) //third
        {
            PlayerSrc = {170, 1214, 45, 65};
        }
        else if (MoveCount==3) //fourth
        {
            PlayerSrc = {215, 1211, 60, 64};
        }
        else if (MoveCount==4) //fifth
        {
            PlayerSrc = {276, 1214, 54, 65};
        }
        else if (MoveCount==5) //sixth
        {
            PlayerSrc = {330, 1208, 54, 71};
        }
        else if (MoveCount==6) //seventh
        {
            PlayerSrc = {381, 1215, 49, 64};
        }
        else if (MoveCount==7) //eight
        {
            PlayerSrc = {436, 1215, 47, 64};
        }
        else if (MoveCount==8) //ninth
        {
            PlayerSrc = {486, 1209, 55, 71};
        }
        else if (MoveCount==9) //tenth
        {
            PlayerSrc = {543, 1207, 64, 74};
        }
        else if (MoveCount==10) //ninth
        {
            PlayerSrc = {609, 1208, 63, 75};
        }
        else if (MoveCount==11) //ninth
        {
            PlayerSrc = {673, 1209, 59, 72};
            MoveCount=2;
        }
        MoveCount++;
    }
    else //no longer moving thus reset
    {
        PlayerSrc = {3,1219,58,62};
        MoveCount = 0;
    }
}

void Player::BasicSword() //attack mapped to key 'g'
{
    if (SwordCount==0)
    {
        PlayerSrc = {3,1219,58,62};
    }
    else if (SwordCount==1)
    {
        PlayerSrc = {5, 629, 58, 48};
    }
    else if (SwordCount==2)
    {
        PlayerSrc = {59, 629, 53, 51};
    }
    else if (SwordCount==3)
    {
        PlayerSrc = {111, 628, 80, 51};
    }
    else if (SwordCount==4)
    {
        PlayerSrc = {188, 628, 101, 51};
    }
    else if (SwordCount==5)
    {
        PlayerSrc = {290, 627, 98, 51};
    }
    else if (SwordCount==6)
    {
        PlayerSrc = {385, 628, 83, 47};
    }
    else if (SwordCount==7)
    {
        PlayerSrc = {467, 629, 66, 50};
        
    }
    else if (SwordCount==8)
    {
        PlayerSrc = {3,1219,58,62};
        SwordCount = -1;
    }
    SwordCount++;
}

void Player::AdvancedSword() //attack mapped to key 'h'
{
    if (AdSword == 0)
    {
        PlayerSrc = {3,1219,58,62};
    }
    else if (AdSword == 1)
    {
        PlayerSrc = {5, 335, 50, 56};
    }
    else if (AdSword == 2)
    {
        PlayerSrc = {51, 321, 59, 70};
    }
    else if (AdSword == 3)
    {
        PlayerSrc = {110, 307, 55, 86};
    }
    else if (AdSword == 4)
    {
        PlayerSrc = {168, 314, 88, 80};
    }
    else if (AdSword == 5)
    {
        PlayerSrc = {256, 325, 61, 70};
    }
    else if (AdSword == 6)
    {
        PlayerSrc = {3,1219,58,62};
        AdSword = -1;
    }
    AdSword++;
}

void Player::hurt()
{
    if (hurtCount==0)
    {
        PlayerSrc = {3,1219,58,62};
    }
    else if (hurtCount==1)
    {
        PlayerSrc = {0,2160,55,59};
    }
    else if (hurtCount ==2)
    {
        PlayerSrc = {51, 2157, 67, 64};
    }
    else if (hurtCount == 3)
    {
        PlayerSrc = {118, 2158, 65, 68};
    }
    else if (hurtCount ==4)
    {
        PlayerSrc = {181, 2158, 94, 58};
    }
    else if (hurtCount==5)
    {
        PlayerSrc = {278, 2160, 68, 58};
    }
    else if (hurtCount == 6)
    {
        PlayerSrc = {3,1219,58,62};
        hurtCount=-1;
    }
    hurtCount++;
}

void Player::draw(SDL_Renderer* gRenderer, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(gRenderer, assets, &PlayerSrc, &mover, 0, NULL, flip);
}

void Player::reduceHealth()
{
    health--;
    cout<<health<<endl;
}

void Player::celebration()
{
    if (celebCount == 0)
    {
        PlayerSrc = {328, 2637,55,71};
    }
    else if (celebCount==1)
    {
        PlayerSrc = {384, 2639,54, 71};
    }
    else if (celebCount==2)
    {
        PlayerSrc = {437, 2636,53, 73};
    }
    else if (celebCount==3)
    {
        PlayerSrc = {488, 2641, 55, 68};
    }
    else if (celebCount==4)
    {
        PlayerSrc = {543, 2646, 53, 65};
    }
    else if (celebCount==5)
    {
        PlayerSrc = {600, 2643, 47, 70};
    }
    else if (celebCount==6)
    {
        PlayerSrc = {652, 2645, 54, 68};
    }
    else if (celebCount==7)
    {
        PlayerSrc = {708, 2646, 60, 71};
    }
    else if (celebCount ==8)
    {
        PlayerSrc = {770, 2648, 57, 68};
    }
    else if (celebCount==9)
    {
        PlayerSrc = {823, 2650, 61, 66};
        celebCount=-1;
    }
    if (celebCount == 10)
    {
        PlayerSrc = {328, 2637,55,71};
    }
    else if (celebCount==11)
    {
        PlayerSrc = {384, 2639,54, 71};
    }
    else if (celebCount==12)
    {
        PlayerSrc = {437, 2636,53, 73};
    }
    else if (celebCount==13)
    {
        PlayerSrc = {488, 2641, 55, 68};
    }
    else if (celebCount==14)
    {
        PlayerSrc = {543, 2646, 53, 65};
    }
    else if (celebCount==15)
    {
        PlayerSrc = {600, 2643, 47, 70};
    }
    else if (celebCount==16)
    {
        PlayerSrc = {652, 2645, 54, 68};
    }
    else if (celebCount==17)
    {
        PlayerSrc = {708, 2646, 60, 71};
    }
    else if (celebCount ==18)
    {
        PlayerSrc = {770, 2648, 57, 68};
    }
    else if (celebCount==19)
    {
        PlayerSrc = {823, 2650, 61, 66};
        celebCount=-1;
    }
    celebCount++;
}


void Player::stateReset()
{
    mover = {300, 500, 75, 100};
    MoveCount = 0;
    SwordCount = 0;
    AdSword = 0;
    hurtCount = 0;
    flip = SDL_FLIP_NONE;
    health = 10;
    celebCount = 0;
}

void Player::stateLoad()
{
    ifstream myfile("save.txt");
    if (!(myfile.peek() == std::ifstream::traits_type::eof()))
	{
        string line1, line2, line3, line4;

        getline(myfile, line1);

        getline(myfile, line2);

        getline(myfile, line3);

        getline(myfile, line4);

        myfile.close();

        health = stoi(line1);
        AdSword = stoi(line2);
        hurtCount = stoi(line3);
        celebCount = stoi(line4);
    }
}

void Player::stateWrite()
{
    ofstream myfile("save.txt");
    myfile << health << endl << AdSword << endl << hurtCount << endl << celebCount << endl;
    myfile.close();
}

void Player::operator = (int &applesLeft)
{
    applesLeft = health;
}

void Player::operator ++ ()
{
    health++;
}

void Player::operator -- ()
{
    health--;
    cout<<"Player health: "<<health<<endl;
}


#include "game.hpp"
bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "The Adventures of Aladdin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	//Loading success flag
	bool success = true;
	
	assets = loadTexture("Aladdin_trans.png");
	Eassets = loadTexture("Enemies_Sprite_1_trans.png");
	Aassets = loadTexture("alien.png");
	Iassets = loadTexture("items_spritesheet.png");
    gTexture = loadTexture("background.png");
	Jassets = loadTexture("jasmine.png");
	gBackgroundTexture = loadTexture("agrabahbackground.jpg");
	gButtonSpriteSheetTexture1 = loadTexture("New game Button.png");
	gButtonSpriteSheetTexture2 = loadTexture("Load Button.png");
	gVolumeButtonTexture = loadTexture("musicbutton.png");	
	gMuteButtonTexture = loadTexture("mutebutton.png");	
	gQuitButtonTexture = loadTexture("quitbutton.png");
	gVictoryButtonTexture = loadTexture("victory.png");	
	gLoseButtonTexture = loadTexture("gameover.png");

	if(assets==NULL || gTexture==NULL || Eassets==NULL || Aassets==NULL || Iassets==NULL || Jassets==NULL 
	|| gBackgroundTexture == NULL || gButtonSpriteSheetTexture1==NULL || gButtonSpriteSheetTexture2 == NULL 
	|| gVolumeButtonTexture == NULL || gMuteButtonTexture == NULL || gQuitButtonTexture == NULL 
	|| gVictoryButtonTexture == NULL || gLoseButtonTexture == NULL)
    {
        printf("Unable to run due to error: %s\n",SDL_GetError());
        success =false;
    }
	
	bgMusic = Mix_LoadMUS( "JAWS  Main Title.mp3" );

	if(bgMusic == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
	return success;
}

void Game::close()
{
	//Free loaded images
	SDL_DestroyTexture(assets);
	assets=NULL;
	SDL_DestroyTexture(Eassets);
	Eassets=NULL;
	SDL_DestroyTexture(Aassets);
	Aassets=NULL;
	SDL_DestroyTexture(Iassets);
	Iassets=NULL;
	SDL_DestroyTexture(Jassets);
	Jassets=NULL;
	SDL_DestroyTexture(gTexture);
	SDL_DestroyTexture(gBackgroundTexture);
	SDL_DestroyTexture(gButtonSpriteSheetTexture1);
	SDL_DestroyTexture(gButtonSpriteSheetTexture2);
	SDL_DestroyTexture(gVolumeButtonTexture);
	SDL_DestroyTexture(gMuteButtonTexture);
	SDL_DestroyTexture(gQuitButtonTexture);
	SDL_DestroyTexture(gVictoryButtonTexture);
	SDL_DestroyTexture(gLoseButtonTexture);
	deleteAllObjects(enemys, items);	
	
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	Mix_FreeMusic(bgMusic);
	bgMusic = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

SDL_Texture* Game::loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void Game::deleteAllObjects(list<Enemy*> &enemys, list<Obstacles*> &items)
{
	for (auto &i: enemys)
	{
		Enemy *temp = i;
		enemys.remove(i);
		delete(temp);
	}
	for (auto &j: items)
	{
		Obstacles *temp = j;
		items.remove(j);
		delete(temp);
	}
}

void Game::EnemyAttack(SDL_Rect bgSRC, Player *ptr, SDL_RendererFlip flip, bool flag3)
{
	for (auto i: enemys)
	{
		SDL_Rect b = i -> getMover();
		SDL_Rect a = ptr -> getMover();
		SDL_bool collision = SDL_HasIntersection(&a, &b);
		int random = rand() % 100 + 1;
		if (collision)
		{
			if (random < 20)
			{
				for (int j = 0; j < 7; j++)
				{
					SDL_RenderClear(gRenderer);
            		SDL_RenderCopy(gRenderer, gTexture, &bgSRC, NULL);
					i -> attack(gTexture, bgSRC);
					i -> draw(gRenderer);
					ptr -> hurt();
					ptr -> draw(gRenderer, flip);
					drawAllItems(flip, flag3);
					status(gRenderer, Iassets);
            		SDL_RenderPresent(gRenderer);
            		SDL_Delay(80);
				}
				--(*ptr);
				(*ptr) = applesLeft;
				if (applesLeft == 0)
				{
					play = false;
					lose = true;
				}
			}
		}
	}
}

void Game::status(SDL_Renderer* gRenderer, SDL_Texture* assets) //the health meter and lamp score
{
	SDL_Rect statusSrc, statusMover;
	statusSrc = {44, 168, 114, 17}; //render first the sign 'health meter'
	statusMover = {20, 50, 100, 40}; //place the sign 'health meter'
	SDL_RenderCopy( gRenderer, assets, &statusSrc, &statusMover ); //render the sign 'health meter'
	statusMover.x = 120; //update x value for placement of apples
	statusMover.y = 60;//update y value for placement of apples
	for(int i=0;i<applesLeft;i++) //render the apples in accordance to health of player
	{
		statusSrc = {339, 14, 15, 18};
		statusMover.x+=20;
		statusMover.w=20;
		statusMover.h=20;
		SDL_RenderCopy( gRenderer, assets, &statusSrc, &statusMover );		
	}

	//the points
	statusSrc = {248, 110, 43, 16}; //the point sign
	statusMover = {20, 100, 50, 40};
	SDL_RenderCopy( gRenderer, assets, &statusSrc, &statusMover );
	statusMover.x = 120; //update x value for placement of apples
	statusMover.y = 100;
	for(int i=0;i<points;i++)
	{
		statusSrc = {32, 951, 52, 29};
		statusMover.x+=20;
		statusMover.w=30;
		statusMover.h=30;
		SDL_RenderCopy( gRenderer, assets, &statusSrc, &statusMover );

	}
}

void Game::playerAttack(Player* ptr, SDL_RendererFlip flip, char ch, SDL_Rect bgSRC, bool flag3)
{
	SDL_Rect a = ptr -> getMover();
	int health;
	for (auto i: enemys)
	{
		SDL_Rect b = i -> getMover();
		i -> checkCollison(a, b, flip, ch);
		if ((*i) <= 0)
		{
			for (int j=0; j<3; j++)
			{
				SDL_RenderClear(gRenderer);
				SDL_RenderCopy(gRenderer, gTexture, &bgSRC, NULL);
				i -> hurt();
				i -> draw(gRenderer);
				drawAllItems(flip, flag3);
				ptr -> draw(gRenderer, flip);
				status(gRenderer, Iassets);
				SDL_RenderPresent(gRenderer);
				SDL_Delay(80);
			}

			Enemy *temp = i;
			enemys.remove(i);
			delete(temp);
			points+=1;
		}
	}
}


// Drawing all the enemies.
void Game::drawAllObjects(int mx, bool flag,bool flag2,SDL_RendererFlip flip, bool flag3)
{
	for (auto i: enemys)    
	{
		i -> move(mx, flag, flag2, flip); //move the enemy
		i -> draw(gRenderer);		//then draw the enemy
	}
}

void Game::drawAllItems(SDL_RendererFlip flip, bool flag3)
{
	for (auto j: items)
	{
		j -> draw(gRenderer);
		j -> move(flip, flag3);
	}
}

void Game::drawJas(bool flag4, SDL_RendererFlip flip)
{
	
	for (auto k: jasList)
	{
		k -> draw(gRenderer);
		k -> Move(flag4, flip);
	}
}

void Game::objectCollision(Player* ptr)
{
	SDL_Rect a = ptr -> getMover();
	bool collision;
	char temp;
	for (auto i: items)
	{
		SDL_Rect b = i -> getMove();
		collision = SDL_HasIntersection(&a, &b);

		if (collision)
		{
			temp = i -> name();
			if (temp == 'P')
			{
				++(*ptr);
				(*ptr) = applesLeft;
			}
			else
			{
				points++;
			}

			delete(i);
			items.remove(i);
			

		}
	}
}

void Game::JasmineCollision(Player * ptr, SDL_Rect &bgSRC, SDL_RendererFlip flip)
{
	SDL_Rect a = ptr -> getMover();
	bool collision;
	for (auto i: jasList)
	{
		SDL_Rect b = i -> getMover();
		collision = SDL_HasIntersection(&a, &b);

		if (collision)
		{
			delete(i);
			jasList.remove(i);

			for (int j=0; j<20; j++)
			{
				SDL_RenderClear(gRenderer);
				SDL_RenderCopy(gRenderer, gTexture, &bgSRC, NULL);
				ptr -> celebration();
				ptr -> draw(gRenderer, flip);
				status(gRenderer, Iassets);
				SDL_RenderPresent(gRenderer);
				SDL_Delay(80);
			}
			play = false;
			victory  =true;
		}
	}

}

void Game::run( )
{
	bool quit=false; 
	paused = false;
	play = false;
	music = false;
	victory = false;
	lose = false;

	SDL_Event e;
	SDL_Rect bgSRC = {0,0,729,689};
	SDL_bool collision; //falg variable for checking player collision with all Menu objects
	Player *ptr = Player::getInstance(assets);   //aladdin
	int &x = bgSRC.x;
	int px = 0;  // Player's virtual position initialied to 0 at the start of the level.
	int enyval = 1500; //will be randomly picked.
	int appleval = 1000;
	int lampval = 2000;
	bool flag = false; //flag for the BigGuard to allow its creation.
	
	bool flag2 = true; //flag for preventing movement but allowing enemy move animation.
	
	bool flag3 = false; //flag for item movement

	bool flag4 = false; //flag for jasmine movement

	SDL_RendererFlip flip; //the flip flag to record the orientation of the player object
	SDL_RenderClear(gRenderer);  
	SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);

	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}

			
			if (play == false && victory == false && lose == false)
			{
				SDL_RenderClear( gRenderer );
				SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
				//Render buttons
				SDL_RenderCopy(gRenderer, gButtonSpriteSheetTexture1, NULL, &g1);
				SDL_RenderCopy(gRenderer, gButtonSpriteSheetTexture2, NULL, &g2);
				if (music == false)
				{
					SDL_RenderCopy(gRenderer, gVolumeButtonTexture, NULL, &g3);
				}
				else
				{
					SDL_RenderCopy(gRenderer, gMuteButtonTexture, NULL, &g3);
				}
				SDL_RenderPresent(gRenderer);
				SDL_Delay(80);
				mouseOnBackgroundButton(&e, *(ptr), bgSRC, px, enyval, appleval, lampval);
				}
			else if (play == false && victory == true && lose == false)
			{
				Mix_HaltMusic();
				SDL_RenderClear( gRenderer );
				SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
				SDL_RenderCopy(gRenderer, gVictoryButtonTexture, NULL, &g1);
				SDL_RenderCopy(gRenderer, gQuitButtonTexture, NULL, &g6);
				SDL_RenderPresent(gRenderer);
				mouseOnQuitButton(&e, *(ptr), bgSRC, 0, px);
				SDL_Delay(80);
			}
			else if (play == false && victory == false && lose == true)
			{
				Mix_HaltMusic();
				SDL_RenderClear( gRenderer );
				SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
				SDL_RenderCopy(gRenderer, gLoseButtonTexture, NULL, &g5);
				SDL_RenderCopy(gRenderer, gQuitButtonTexture, NULL, &g6);
				SDL_RenderPresent(gRenderer);
				mouseOnQuitButton(&e, *(ptr), bgSRC, 0, px);
				SDL_Delay(80);
			}
			
			else if (play == true)
			{
				if(e.type == SDL_KEYDOWN)	
				{
					if (e.key.keysym.sym == SDLK_ESCAPE) //escape key detected
					{
						paused =  !(paused); //toggle pause - true/false - depending on previous state
					}
				}
				if (paused == false)
				{
					if(e.type == SDL_KEYDOWN)	
					{
						if (e.key.keysym.sym == SDLK_RIGHT)
						{
							//flag2 = true;
							flip = SDL_FLIP_NONE;
							flag3 = true; //items flag
							flag4 = true; //jasmine flag
							ptr -> HorizontalMove(true, x, px, flip);
						}
						else if (e.key.keysym.sym == SDLK_LEFT)
						{
							flag2 = true; //enemy flag
							flag3 = true; //items flag
							flag4 = true; //jasmine flag
							flip = SDL_FLIP_HORIZONTAL;
							ptr -> HorizontalMove(true, x, px, flip);
						}
						else if (e.key.keysym.sym == SDLK_g)
						{
							ptr -> BasicSword();
						}
						else if (e.key.keysym.sym == SDLK_h)
						{
							ptr -> AdvancedSword();
						}
					}
					else if (e.type == SDL_KEYUP)
					{
						if (e.key.keysym.sym == SDLK_RIGHT)
						{
							//flag2 = false;
							flag3 = false; //items flag
							flag4 = false; //jasmine flag
							flip = SDL_FLIP_NONE;
							ptr -> HorizontalMove(false, x, px, flip);
						}
						else if (e.key.keysym.sym == SDLK_LEFT)
						{
							flag2 = false; //enemy
							flag3 = false; //item
							flag4 = false; //jasmine flag
							flip = SDL_FLIP_HORIZONTAL;
							ptr -> HorizontalMove(false, x, px, flip);
						}
						else if (e.key.keysym.sym == SDLK_g)
						{
							SDL_Rect a = ptr -> getMover();
							//SDL_Rect b = bguard.getMover();
							for (int i=0; i<8; i++) //run loop of 8 (because 8 sword animation frames) to complete the animation when user lifts off the g key
							{
								SDL_RenderClear(gRenderer);
								SDL_RenderCopy(gRenderer, gTexture, &bgSRC, NULL);
								ptr -> BasicSword();
								ptr -> draw(gRenderer, flip);
								status(gRenderer, Iassets);
								drawAllObjects(a.x, flag, flag2, flip, flag3);
								JasmineCollision(ptr, bgSRC, flip);
								drawJas(flag4, flip);
								drawAllItems(flip, flag3);
								SDL_RenderPresent(gRenderer);
								SDL_Delay(80);
							}
							playerAttack(ptr, flip, 'b', bgSRC, flag3);
							
						}
						else if (e.key.keysym.sym == SDLK_h)
						{
							SDL_Rect a = ptr -> getMover();
							//SDL_Rect b = bguard.getMover();
							for (int i=0; i<6; i++) //run loop of 8 (because 8 sword animation frames) to complete the animation when user lifts off the g key
							{
								SDL_RenderClear(gRenderer);
								SDL_RenderCopy(gRenderer, gTexture, &bgSRC, NULL);
								ptr -> AdvancedSword();
								ptr -> draw(gRenderer, flip);
								status(gRenderer, Iassets);
								drawAllObjects(a.x, flag, flag2, flip, flag3);
								JasmineCollision(ptr, bgSRC, flip);
								drawAllItems(flip, flag3);
								drawJas(flag4, flip);
								//bguard.draw(gRenderer);
								//collision = SDL_HasIntersection(&a, &b);
								SDL_RenderPresent(gRenderer);
								SDL_Delay(80);
							}
							playerAttack(ptr, flip, 'a', bgSRC, flag3);
						}
					}
					if (music == false)
					{
						if( Mix_PlayingMusic() == 0 )
						{
							//Play the music
							Mix_PlayMusic( bgMusic, 2 );
						}
					}
					SDL_RenderClear(gRenderer); //removes everything from renderer
					SDL_RenderCopy(gRenderer, gTexture, &bgSRC, NULL);//Draws background to renderer
					//**********************draw the objects here********************
					if (px >= enyval)
					{
						if (bGuardCount < 3)
						{
							flag = true;
							FactoryEnemy *factory = new FactoryEnemy(1, Eassets);
							Enemy *eny = factory -> getEnemy();
							enemys.push_back(eny);
							int temp = rand() % 2000 + 1;
							enyval = enyval + temp;
							bGuardCount++;

						}
						
					}

					if (px >= enyval && bGuardCount == 3)
					{
						if (smanCount < 3)
						{
							flag = true;
							FactoryEnemy *factory = new FactoryEnemy(2, Eassets);
							Enemy *eny = factory -> getEnemy();
							enemys.push_back(eny);
							int temp = rand() % 2000 + 1;
							enyval = enyval + temp;
							smanCount++;
							
							
						}
						
					}


					if (px >= enyval && bGuardCount == 3  && smanCount == 3)
					{
						if (alienCount < 3)
						{
							flag = true;
							FactoryEnemy *factory = new FactoryEnemy(3, Aassets);
							Enemy *eny = factory -> getEnemy();
							enemys.push_back(eny);
							int temp = rand() % 2000 + 1;
							enyval = enyval + temp;
							alienCount++;
							
						}

						else
						{
							enyval = enyval + 1000;
						}
						
						
					}

					if (enemys.empty() && bGuardCount == 3  && smanCount == 3 && alienCount == 3)
					{
						//cout<<"create jasmine"<<endl;
						if (jasCount == 0)
						{
							//cout<<"create jasmine"<<endl;
							Jasmine* jas = Jasmine::getInstance(Jassets);
							jasList.push_front(jas);
							jasCount++;
						}
					}


					if (px >= appleval)
					{
						FactoryObstacles *factory = new FactoryObstacles(1, Iassets);
						Obstacles *obs = factory -> getObstacles();
						items.push_back(obs);
						int temp = rand() % 2500 + 1;
						appleval = appleval + temp;
					}

					if (px >= lampval)
					{
						FactoryObstacles *factory = new FactoryObstacles(2, Iassets);
						Obstacles *obs = factory -> getObstacles();
						items.push_back(obs);
						int temp = rand() % 4500 + 1;
						lampval = lampval + temp;
						
					}

					ptr -> draw(gRenderer, flip);
					SDL_Rect a = ptr -> getMover();
					objectCollision(ptr);
					drawAllObjects(a.x, flag, flag2, flip, flag3);
					drawJas(flag4, flip);
					JasmineCollision(ptr, bgSRC, flip);
					drawAllItems(flip, flag3);
					status(gRenderer, Iassets);
					EnemyAttack(bgSRC, ptr, flip, flag3);
					//****************************************************************
					SDL_RenderPresent(gRenderer); //displays the updated renderer

					SDL_Delay(80);	//causes sdl engine to delay for specified miliseconds - affects speed of animation	
				}
				else if (paused == true)
				{
					Mix_HaltMusic();
					SDL_RenderClear( gRenderer );
					SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
					SDL_RenderCopy(gRenderer, gQuitButtonTexture, NULL, &g4);
					SDL_RenderPresent(gRenderer);
					mouseOnQuitButton(&e, *(ptr), bgSRC);
					SDL_Delay(80);
				}		
			}
		}
	}	
	
}

void writeBGToFile(SDL_Rect r, int points, list<Enemy*> &enemys, list<Obstacles*> &obs)
{
	ofstream myfile("save.txt", ios::app);
    myfile << r.x << endl;
	myfile << points << endl;

	for (auto a: enemys)
	{
		a -> createOutFile(myfile);
	}
	myfile << endl;
	for (auto b: obs)
	{
		b ->createOutFile(myfile);
	}

    myfile.close();
}
void Game::readBGFromFile(SDL_Rect &r, int &points)
{
	ifstream myfile("save.txt");
	if (!(myfile.peek() == std::ifstream::traits_type::eof()))
	{
		stringstream ss;
		string line1, line2, line3, linevar1, linevar2, linevar3;
		int bg, pts;

		getline(myfile, line1);
		getline(myfile, line1);
		getline(myfile, line1);
		getline(myfile, line1);

		getline(myfile, line2);
		getline(myfile, line3);

		r.x = stoi(line2);
		points = stoi(line3);

		while (getline(myfile, linevar1))
		{
			if (linevar1.empty())
			{
				break;
			}
			if (linevar1 == "A")
			{
				Enemy *eny = new Alien(Aassets);
				getline(myfile, linevar2);
				getline(myfile, linevar3);
				eny->setHealthnMover(stoi(linevar2), stoi(linevar3));
				enemys.push_back(eny);
			}
			else if (linevar1 == "B")
			{
				Enemy *eny = new BigGuard(Eassets);
				bGuardCount++;
				getline(myfile, linevar2);
				getline(myfile, linevar3);
				eny->setHealthnMover(stoi(linevar2), stoi(linevar3));
				enemys.push_back(eny);
			}
			else if (linevar1 == "S")
			{
				Enemy *eny = new StickMan(Eassets);
				smanCount++;
				getline(myfile, linevar2);
				getline(myfile, linevar3);
				eny->setHealthnMover(stoi(linevar2), stoi(linevar3));
				enemys.push_back(eny);
			}	
		}

		while (getline(myfile, linevar1))
		{
			if (linevar1 == "P")
			{
				Obstacles *item = new Apple(Iassets);
				items.push_back(item);
				getline(myfile, linevar2);
				item->setMove(stoi(linevar2));
			}
			else if (linevar1 == "L")
			{
				Obstacles *item2 = new Lamp(Iassets);
				items.push_back(item2);
				getline(myfile, linevar2);
				item2->setMove(stoi(linevar2));
			}
		}
	}
    myfile.close();
}

void Game::mouseOnBackgroundButton(SDL_Event* e, Player &p, SDL_Rect &bgSRC, int &px, int &enyval, int& appleval, int& lampval)
{
	int xMouse, yMouse;
	SDL_GetMouseState(&xMouse,&yMouse);
	SDL_Rect mouse = {xMouse, yMouse, 1, 1};
	if (SDL_HasIntersection(&mouse, &g1) && (e->type == SDL_MOUSEBUTTONDOWN))
	{
		play = true;
		px = 0;
		enyval = 1500;
		jasCount = 0;
		appleval = 1000;
		lampval = 2000;
		ofstream ofs;
		ofs.open("save.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		bGuardCount = smanCount = alienCount = 0;
		gameReset(p, bgSRC);
		deleteAllObjects(enemys, items);
	}
	else if (SDL_HasIntersection(&mouse, &g2) && (e->type == SDL_MOUSEBUTTONDOWN))
	{
		gameReset(p, bgSRC);
		play = true;
		p.stateLoad();
		readBGFromFile(bgSRC, points);
		applesLeft = p.getHealth();
	}
	else if (SDL_HasIntersection(&mouse, &g3) && (e->type == SDL_MOUSEBUTTONDOWN))
	{
		music = !(music);
	}
}
void Game::mouseOnQuitButton(SDL_Event* e,  Player &p, SDL_Rect &bgSRC)
{
	int xMouse, yMouse;
	SDL_GetMouseState(&xMouse,&yMouse);
	SDL_Rect mouse = {xMouse, yMouse, 1, 1};
	if (SDL_HasIntersection(&mouse, &g4) && (e->type == SDL_MOUSEBUTTONDOWN))
	{
		play = false;
		paused = false;
		p.stateWrite();
		writeBGToFile(bgSRC, points, enemys, items);
		deleteAllObjects(enemys, items);
	}
}
void Game::mouseOnQuitButton(SDL_Event* e,  Player &p, SDL_Rect &bgSRC, bool low, int &px)
{
	int xMouse, yMouse;
	SDL_GetMouseState(&xMouse,&yMouse);
	SDL_Rect mouse = {xMouse, yMouse, 1, 1};
	if (SDL_HasIntersection(&mouse, &g6) && (e->type == SDL_MOUSEBUTTONDOWN))
	{
		play = paused = victory = lose = false;
		px = 0;
		ofstream ofs;
		ofs.open("save.txt", std::ofstream::out | std::ofstream::trunc);
		ofs.close();
		gameReset(p, bgSRC);
		deleteAllObjects(enemys, items);
	}
}

void Game::gameReset(Player &p, SDL_Rect &bgSRC)
{
	p.stateReset();
	deleteAllObjects(enemys, items);
	bgSRC.x = 0;
	applesLeft = 10;
	points = 0;
}

//g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
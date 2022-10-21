#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace sf;

class Game
{
private : 
	//Variables
	RenderWindow *app;
	Event sfEvent;


	//Initialization
	void initApp();

	//Constructors/Destructors
	
public :
	Game();
	virtual ~Game();

	// ÇÔ¼ö
	void updateSFMLEvents();
	void update();
	void updateDt(); 
	void render();
	void run();
};

#endif

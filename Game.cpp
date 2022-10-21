#include "Game.hpp"


//Initializer function
void Game::initApp()
{
	this->app = new RenderWindow(VideoMode(WIDTH, HEIGHT), "platformer");
	
}

Game::Game() {
	app->setFramerateLimit(60);
	initApp();
	
}

Game::~Game() {
	delete this->app;
}

// functions

void Game::updateSFMLEvents()
{
	
		while (app->pollEvent(sfEvent)) {
			if (sfEvent.type == Event::Closed) app->close();
		}
}

void Game::update()
{
	updateSFMLEvents();
}

void Game::render()
{
	app->clear();

	// Render items

	app->display();
}

void Game::run()
{
	
}


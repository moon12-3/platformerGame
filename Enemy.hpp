#pragma once
#define ENEMY_SPEED 6
#include <SFML/Graphics.hpp>
#include "Global.hpp"

using namespace sf;

class Enemy
{
	bool dead;
	RectangleShape sprite;
	Texture texture;
	float x, y;
	int deathTimer;
public :
	Enemy(float, float);
	void die();
	void draw(RenderWindow& app);
	void update();
};


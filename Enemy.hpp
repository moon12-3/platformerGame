#pragma once
#define ENEMY_SPEED 6
#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Player.hpp"
#include "Collider.hpp"

using namespace sf;

class Enemy : public Player
{
	Texture texture;
	Vector2f velocity;
	float x, y;
	int deathTimer;
public :
	int direction;
	Enemy(float, float);
	void draw(RenderWindow& app);
	Collider getCollider() { return Collider(sprite); }
	void update();
};


#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.hpp"

#define GRAVITY 1
#define SPEED 2.4

using namespace sf;

class Player
{
	bool playerFaceRight;
	bool onGround;
	float vertical_speed;
	float x;
	float y;
	float x_speed;

	Texture texture;

	Sprite sprite;

	Clock game_clock;

	float fps;
public :
	Player();

	void draw(sf::RenderWindow& i_window, int n, Sprite* block);
	void update(int n, Sprite* block);
	bool isCollide(Sprite s1, Sprite s2);
	Vector2f getPosition() { return sprite.getPosition(); }
	Collider GetCollider() { return Collider(sprite); }

};
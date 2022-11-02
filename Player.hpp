#pragma once
#include<SFML/Graphics.hpp>
#include"Global.hpp"
#include "Collider.hpp"
#include "Coin.hpp"
#include "GameTile.hpp"

#define GRAVITY 7
#define SPEED 7

using namespace sf;

class Player
{
public :
	bool onGround;
	float vertical_speed;
	float x;
	float y;
	float x_speed;
	float fps;
	bool isJumping = false;
	bool canJump;
	float jumpHeight;
	bool faceRight;
	unsigned int row;
	Vector2f velocity;

	Vector2u textureSize;
	Texture texture;
	RectangleShape sprite;
	Clock game_clock;
public :
	Player();

	void draw(sf::RenderWindow& i_window);
	void update(float deltaTime);
	bool isCollidingWithCoin(Coin* coin);
	float getPositionX() { return sprite.getPosition().x+CELL_SIZE/2; }
	Vector2f getPosition() { return sprite.getPosition(); }
	Collider getCollider() { return Collider(sprite); }
	void drawTo();
	void move();
	int getY() {
		return sprite.getPosition().y;
	}
};
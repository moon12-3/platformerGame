#pragma once
#include<SFML/Graphics.hpp>
#include"Global.hpp"
#include "Collider.hpp"
#include "Coin.hpp"
#include "GameTile.hpp"
#include "SFML/Audio.hpp"

#define JUMP_SPEED 9

using namespace sf;

class Player
{
public :
	bool onGround;
	float x;
	float y;
	int hp;
	bool isJumping = false;
	unsigned char jumpTimer;
	unsigned char deathTimer;
	bool canJump;
	float jumpHeight;
	bool faceRight;
	unsigned int row;
	bool dead;
	bool deathScreen;
	Vector2f velocity;
	Vector2u textureSize;
	Texture texture;
	RectangleShape sprite;
	Clock game_clock;

	SoundBuffer buffer;
	Sound jumpSound;
public :
	Player();
	void die();
	void draw(sf::RenderWindow& i_window);
	void update();
	void onCollision(Vector2f direction);
	bool isCollidingWithCoin(Coin* coin);
	float getPositionX() { return sprite.getPosition().x+CELL_SIZE/2; }
	Vector2f getPosition() { return sprite.getPosition(); }
	Collider getCollider() { return Collider(sprite); }
	int getY() {
		return sprite.getPosition().y;
	}
};
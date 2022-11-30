#include"Player.hpp"
#include"Global.hpp"
#include <iostream>

using namespace std;



Player::Player() :
	x(WIDTH*0.5-CELL_SIZE/2),
	y(HEIGHT*0.5-CELL_SIZE/2),
	jumpHeight(SPEED),
	jumpTimer(0),
	onGround(false),
	canJump(true),
	faceRight(true),
	row(0),
	dead(false),
	deathTimer(23),
	hp(3),
	deathScreen(false)
{
	texture.loadFromFile("Resources/Images/Player.png");
	buffer.loadFromFile("Resources/Audio/jump.ogg");
	jumpSound.setBuffer(buffer);
	sprite.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
	sprite.setTexture(&texture);
	sprite.setPosition(round(x), round(y));
}

void Player::draw(sf::RenderWindow& i_window)
{
	// cout << deltaTime << endl;
	i_window.draw(sprite);
	if (!dead)
		update();
	if (sprite.getPosition().y >= HEIGHT - CELL_SIZE || dead) {
		texture.loadFromFile("Resources/Images/playerDeath.png");
		dead = true;
		die();
		
		if (sprite.getPosition().y > HEIGHT + 200) {
			sprite.setPosition(round(x), round(y));
			dead = false;
			hp--;
			texture.loadFromFile("Resources/Images/Player.png");
			deathTimer = 23;
			deathScreen = true;
		}
	}
	//drawTo();
}

void Player::update() {
	velocity.x *= 0.0f;

	if (Keyboard::isKeyPressed(Keyboard::Left) && getPositionX()>=CELL_SIZE/2)
		velocity.x -= SPEED;
	else if (Keyboard::isKeyPressed(Keyboard::Right))
		velocity.x += SPEED;

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		isJumping = true;
	}
	if(isJumping) {
		if (onGround) {
			jumpSound.play();
			velocity.y = -JUMP_SPEED;
			jumpTimer = JUMP_SPEED + 15;
		}
		else if (8 < jumpTimer) {
			velocity.y = -JUMP_SPEED;
			jumpTimer--;
		}
		else if (4 < jumpTimer) {
			velocity.y = -3;
			jumpTimer--;
		}
		else if (0 < jumpTimer) {
			velocity.y = 3;
			jumpTimer--;
		}
		else {
			velocity.y = GRAVITY;
		}
	}
	else
		velocity.y = GRAVITY;

	
	if (velocity.x > 0.0f) faceRight = true;
	else faceRight = false;

	onGround = false;
	sprite.move(velocity);
}

void Player::die()
{
	if (deathTimer == 0)
		sprite.move(0, GRAVITY);
	else if (deathTimer < 13)
		sprite.move(0, -JUMP_SPEED);
	deathTimer = max(0, deathTimer - 1);
}

bool Player::isCollidingWithCoin(Coin* coin)
{
	if (sprite.getGlobalBounds().intersects(coin->getGlobalBounds())) {
		return true;
	}
	return false;
}

void Player::onCollision(Vector2f direction)
{
	if (direction.x < 0.0f) {
		// Collision left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		// right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) {
		// Collision bottom
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f) {
		// Collision Top
		velocity.y = 0.0f;
	}
}
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
	hp(3)
{
	texture.loadFromFile("Resources/Images/Player.png");
	sprite.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
	sprite.setTexture(&texture);
	sprite.setPosition(round(x), round(y));
	deadSprite.setSize(Vector2f(WIDTH, HEIGHT));
	deadSprite.setFillColor(Color(0, 0, 0));
	deadSprite.setPosition(0, 0);
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
		
		if (sprite.getPosition().y > HEIGHT + 100) {
			sprite.setPosition(round(x), round(y));
			dead = false;
			hp--;
			texture.loadFromFile("Resources/Images/Player.png");
			deathTimer = 23;
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
		if (onGround) {
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

	if (velocity.x == 0.0f) {
		row = 0;
	}
	else {
		row = 1;

		if (velocity.x > 0.0f) faceRight = true;
		else faceRight = false;
	}
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

void Player::drawTo()
{
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (onGround && !isJumping) {
			isJumping = true;
			onGround = false;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		sprite.move(Vector2f(SPEED, 0));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left) && sprite.getPosition().x >= 0) {
		sprite.move(Vector2f(-SPEED, 0));
	}
	/*else if (Keyboard::isKeyPressed(Keyboard::Up) && sprite.getPosition().x >= 0) {
		sprite.move(Vector2f(0, -SPEED));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down) && sprite.getPosition().x >= 0) {
		sprite.move(Vector2f(0, SPEED));
	}*/
	if (!onGround && isJumping == false) {
		sprite.move(0, GRAVITY);
	}
	else if (onGround) {
		sprite.move(0, 0);
		// canJump = true;
	}
	onGround = false;
}
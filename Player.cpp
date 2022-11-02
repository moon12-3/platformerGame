#include"Player.hpp"
#include"Global.hpp"
#include <iostream>

using namespace std;



Player::Player() :
	x(WIDTH*0.5-CELL_SIZE/2),
	y(HEIGHT*0.5-CELL_SIZE/2),
	vertical_speed(0),
	x_speed(SPEED),
	onGround(false)
{
	texture.loadFromFile("Resources/Images/Player.png");
	// textureSize = texture.getSize();
	sprite.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
	// sprite.setOrigin(Vector2f(CELL_SIZE, CELL_SIZE) / 2.0f);
	sprite.setTexture(&texture);

	fps = game_clock.restart().asMilliseconds();

	sprite.setPosition(round(x), round(y));
}

void Player::draw(sf::RenderWindow& i_window)
{
	i_window.draw(sprite);

	drawTo();

	//update();

	//sprite.setPosition(Vector2f(x, y));
}

void Player::update(float deltaTime) {
	velocity.x *= 0.0f;
	

	if (Keyboard::isKeyPressed(Keyboard::Left))
		velocity.x -= SPEED;
	if (Keyboard::isKeyPressed(Keyboard::Right))
		velocity.x += SPEED;
	if (Keyboard::isKeyPressed(Keyboard::Space) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
		// square root (2.0f * gravity * jumpHeight);
	}

	velocity.y += GRAVITY * deltaTime;

	if (velocity.x == 0.0f) {
		row = 0;
	}
	else {
		row = 1;

		if (velocity.x > 0.0f) faceRight = true;
		else faceRight = false;
	}

	sprite.move(velocity * deltaTime);
}

bool Player::isCollidingWithCoin(Coin* coin)
{
	if (sprite.getGlobalBounds().intersects(coin->getGlobalBounds())) {
		return true;
	}
	return false;
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
	else if (Keyboard::isKeyPressed(Keyboard::Left) && sprite.getPosition().x>=0) {
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

void Player::move()
{
}

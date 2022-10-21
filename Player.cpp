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
	playerFaceRight = true;
	sprite.setOrigin(Vector2f(CELL_SIZE, CELL_SIZE) / 2.0f);
	sprite.setTexture(texture);

	fps = game_clock.restart().asMilliseconds();

	sprite.setPosition(round(x), round(y));
}

void Player::draw(sf::RenderWindow& i_window, int n, Sprite* block)
{
	i_window.draw(sprite);

	update(n, block);

	sprite.setPosition(Vector2f(x, y));
}

void Player::update(int n, Sprite* block) {
	if (Keyboard::isKeyPressed(Keyboard::LShift)) x_speed = SPEED * 2;
	else x_speed = SPEED;
	 
	if (Keyboard::isKeyPressed(Keyboard::Z)) {

	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		x += x_speed * fps;
		playerFaceRight = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left)) {
		x -= x_speed * fps;
		playerFaceRight = false;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up)) {
		y -= x_speed * fps;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down)) {
		y += x_speed * fps;
	}
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		y -= 25;
	}
	// glitch alert!
	onGround = false;
	for (int i = 0; i < n; i++) {
		if (isCollide(sprite, block[i])) onGround = true;
	}

	if (onGround) vertical_speed = 0;
	else vertical_speed += GRAVITY;

	y += vertical_speed;
}

bool Player::isCollide(Sprite s1, Sprite s2) {	//물체의 충돌을 감지
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}
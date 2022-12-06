#include"Player.hpp"
#include"Global.hpp"
#include <iostream>

using namespace std;



Player::Player() :
	x(WIDTH*0.5-CELL_SIZE/2),	
	y(HEIGHT*0.5-CELL_SIZE/2),	// 맨 처음 화면 가운데에서 시작
	jumpHeight(SPEED),	// jump speed
	jumpTimer(0),
	onGround(false),
	canJump(true),
	faceRight(true),
	row(0),
	dead(false),
	deathTimer(30),
	hp(3),
	deathScreen(false)
{
	texture.loadFromFile("Resources/Images/Player.png");
	buffer.loadFromFile("Resources/Audio/jump.ogg");
	jumpSound.setBuffer(buffer);
	jumpSound.setVolume(20);
	buffer2.loadFromFile("Resources/Audio/dead.ogg");
	deadSound.setBuffer(buffer2);
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
	if (sprite.getPosition().y >= HEIGHT - CELL_SIZE || dead) {	// 땅 아래로 떨어졌거나 dead가 true라면
		
		texture.loadFromFile("Resources/Images/playerDeath.png");	// 죽음 이미지로 전환
		dead = true;
		die();
		
		if (!deadSound.getStatus() && sprite.getPosition().y > HEIGHT) {
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
		

	if (Keyboard::isKeyPressed(Keyboard::Left) && getPositionX()>=CELL_SIZE/2) {
		velocity.x -= SPEED;
		if (faceRight) {
			faceRight = false;
			texture.loadFromFile("Resources/Images/PlayerBack.png");
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && getPositionX() <= W*50-CELL_SIZE / 2) {
		velocity.x += SPEED;
		if (!faceRight) {
			faceRight = true;
			texture.loadFromFile("Resources/Images/Player.png");
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Space)) {
		isJumping = true;
	}
	if(isJumping) {
		if (onGround) {
			jumpSound.play();
			velocity.y = -JUMP_SPEED;
			jumpTimer = JUMP_SPEED + 20;
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

	onGround = false;
	sprite.move(velocity);
}

void Player::die()	// 캐릭터 죽었을 시 살짝 점프 후 떨어지는 모션
{
	if (deathTimer == 0) {
		sprite.move(0, GRAVITY);
	}
	else if (deathTimer == 23)
		deadSound.play();
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
#include "Enemy.hpp"
Enemy::Enemy(float i_x, float i_y) :
	dead(false),
	x(i_x),
	y(i_y),
	deathTimer(15),
	direction(1)
{
	texture.loadFromFile("Resources/Images/enemy.png");
	sprite.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
	sprite.setTexture(&texture);
	sprite.setPosition(round(x), round(y));
}

void Enemy::draw(RenderWindow& app)
{
	app.draw(sprite);
	if (!dead) {
		update();
	}

	if (dead) {
		sprite.setSize(Vector2f(CELL_SIZE, CELL_SIZE/4));
	}
}

void Enemy::update() {
	velocity.x = -SPEED*direction/2;
	velocity.y = GRAVITY;
	sprite.move(velocity);
}
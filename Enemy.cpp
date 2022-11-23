#include "Enemy.hpp"
Enemy::Enemy(float i_x, float i_y) :
	dead(false),
	x(i_x),
	y(i_y),
	deathTimer(15)
{
	texture.loadFromFile("Resources/Images/Enemy.png");
}

void Enemy::die()
{
}

void Enemy::draw(RenderWindow& app)
{
	if (!dead) {
		sprite.setPosition(round(x), round(y));
		sprite.setTexture(&texture);

		app.draw(sprite);
	}

	if (dead) {
		sprite.setSize(Vector2f(CELL_SIZE, CELL_SIZE/4));
	}
}

void Enemy::update() {

}
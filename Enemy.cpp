#include "Enemy.hpp"
Enemy::Enemy(float i_x, float i_y) :
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
	sprite.setTexture(&texture);
	app.draw(sprite);
	if(!dead) {
		update();
	}

	if (dead) {
		texture.loadFromFile("Resources/Images/enemyDeath.png");
		dead = true;
	}
}

void Enemy::update() {
	if(getPositionX()<=0)
		direction = -1;
	velocity.x = -SPEED * direction / 2;	// 왼쪽으로 움직임
	velocity.y = GRAVITY;	// 중력 작동
	sprite.move(velocity);	
}
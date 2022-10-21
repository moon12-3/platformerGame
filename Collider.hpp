#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Global.hpp"

using namespace sf;

class Collider
{
	Sprite body;
public :
	Collider(Sprite);

	void Move(float dx, float dy) { body.move(dx, dy); }
	bool CheckCollision(Collider& other, float push);
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return Vector2f(CELL_SIZE / 2.0f, CELL_SIZE / 2.0f); }
};


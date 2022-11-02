#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Global.hpp"

using namespace sf;

class Collider
{
	RectangleShape& body;
public :
	Collider(RectangleShape&);

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collider& other, Vector2f& direction, float push);
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return body.getSize()/2.0f; }
};


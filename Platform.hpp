#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.hpp"

using namespace sf;

class Platform
{
	Sprite body;

public :
	Platform(Texture texture, float x, float y);
	void Draw(RenderWindow);
	Collider GetCollider() { return Collider(body); }
};


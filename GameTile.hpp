#pragma once
#include<SFML/Graphics.hpp>
#include"Global.hpp"
#include"Player.hpp"
#include <iostream>

using namespace sf;

class GameTile
{
	Vector2f pos;
	Texture texture;
public:
	GameTile(std::string, float, float, char);
	GameTile();
	void setUpSprite(std::string);
	Collider GetCollider() { return Collider(block); }
	char tileType;
	FloatRect getGlobalBounds() {
		return block.getGlobalBounds();
	}

	RectangleShape block;
};


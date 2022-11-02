#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

using namespace sf;

class Coin
{
	RectangleShape coin;
public :
	Coin(Vector2f size) {
		coin.setSize(size);
		coin.setFillColor(Color::Yellow);
	}
	void draw(RenderWindow& app);
	void setPos(Vector2f newPos) {
		coin.setPosition(newPos);
	}

	FloatRect getGlobalBounds() {
		return coin.getGlobalBounds();
	}
};


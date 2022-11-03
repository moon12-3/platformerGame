#pragma once

#include"Player.hpp"
#include"Global.hpp"
#include"Collider.hpp"
#include<iostream>
#include "Coin.hpp"
#include"GameTile.hpp"
#include"GameWorld.hpp"

using namespace sf;

Clock dtClock;
float deltaTime = 0.0f;
float interval = 0;
int minute = 0;
int score = 0;

void ResizeView(RenderWindow& app, View& view)	// 화면 크기 변경 시 조절
{
	float aspecRatio = float(app.getSize().x) / float(app.getSize().y);
	view.setSize(HEIGHT * aspecRatio, HEIGHT);
}

int main() {
	RenderWindow app(VideoMode(WIDTH, HEIGHT), "platformer", Style::Resize | Style::Close);
	View view(Vector2f(0.0f, 0.0f), Vector2f(WIDTH, HEIGHT));
	app.setFramerateLimit(60);

	Texture map_texture;
	map_texture.loadFromFile("Resources/Images/block.png");

	// PlayerW
	Player player;
	Clock clock;
	// Coin
	vector<Coin*> coinVec;
	Coin coin1(Vector2f(20, 20));
	Coin coin2(Vector2f(20, 20));
	coinVec.push_back(&coin1);
	coinVec.push_back(&coin2);

	coin1.setPos(Vector2f(50, 410));
	coin2.setPos(Vector2f(150, 410));

	// Map
	GameWorld gameWorld = GameWorld(&player);

	Font font;
	font.loadFromFile("Resources/Fonts/DungGeunMo.ttf");

	Text text("00:00", font, 50);
	text.setFont(font);

	ostringstream ssScore;
	ssScore << "Score : " << score;

	Text lblScore;
	lblScore.setCharacterSize(30);
	lblScore.setPosition(50, 200);
	lblScore.setFont(font);
	lblScore.setString(ssScore.str());

	while (app.isOpen()) {
		Event e;
		float time = dtClock.getElapsedTime().asSeconds();
		Time elapsed = dtClock.restart();
		interval += time;
		string t = std::to_string((int)interval)+"s";
		text.setString(t);

		deltaTime = clock.restart().asSeconds();

		while (app.pollEvent(e)) {
			switch (e.type)
			{
			case Event::Closed : 
				app.close(); 
				break;	// 닫았을 시
			case Event::Resized: 
				ResizeView(app, view); 
				break;	// 화면 조정 시
			}
		}

		app.setView(view);
		text.setPosition(view.getRotation(), 100);
		if(player.getPositionX()<=WIDTH * 0.5) view.setCenter(WIDTH * 0.5, HEIGHT * 0.5);
		else view.setCenter(player.getPositionX(), HEIGHT * 0.5);

		for (int i = 0; i < coinVec.size(); i++) {
			if (player.isCollidingWithCoin(coinVec[i])) {
				coinVec[i]->setPos(Vector2f(40000, 40000));
				score++;
				ssScore.str("");
				ssScore << "Score : " << score;
				lblScore.setString(ssScore.str());
			}
		}
		app.clear(Color(98, 172, 255));
		gameWorld.draw(app);
		app.draw(text);
		coin1.draw(app);
		coin2.draw(app);
		app.draw(lblScore);
		player.draw(app);

		app.display();

	} 
	return 0;
}

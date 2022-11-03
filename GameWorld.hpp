#pragma once

#include<SFML/Graphics.hpp>
#include "GameTile.hpp"
#include "Player.hpp"
#include "Collider.hpp"
#include<vector>
#include<algorithm>
#include<fstream>
#include<iostream>
#include<string>

using namespace sf;
using namespace std;

class GameWorld
{
	Vector2i exitPos;
	vector<Vector2i> enemyPos;
	void setUpInitialState();
	void setUpEnemyPositions();
	void setUpTiles();
	void createMap(std::string);
	char tileType;
	std::vector<std::string> lines;
	Player* p;
	string tile[H] = {
		"00000000000000000000000000000000",
		"00000000000000000000000000000000",
		"00000000000000000000000000000000",
		"00000000000000000000000000000000",
		"00000000000000000000000000000000",
		"00000000000000000000000000000000",
		"00000002220000000000000000000000",
		"00222000000000000000000000001000",
		"00000000000000000000000000101000",
		"0000000ab00000000000000010101000",
		"11111111111111111111100111111111",
		"11111111111111111111100111111111"
	};
public :
	vector<vector<GameTile* >> tiles;
	int gridLength;
	GameWorld(Player*);
	void draw(RenderWindow&);
};


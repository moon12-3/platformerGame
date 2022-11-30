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
#include"Enemy.hpp"
#include"Global.hpp"

using namespace sf;
using namespace std;

class GameWorld
{
	Vector2i exitPos;
	vector<Vector2i> enemyPos;
	void setUpTiles();
	void createMap(std::string);
	char tileType;
	int i;
	std::vector<std::string> lines;
	Player* p;
	vector<Enemy*> goombas;
	string tile[H] = {
		"0000000000000000000000000000000000000000000000000000000000000000",
		"0000000000000000000000000000000000000000000000000000000000000000",
		"000000000000000000000000000000000c00000000000000000000000c000000",
		"00000000000000c0000000000000000000000000000000c00000000000000000",
		"0000000000000000000000c00000000000000000000000000000000000000000",
		"0000000000000000000000000000000000000000000000000000000000000000",
		"0000000000000222000000000000000000000000000000000000000000000000",
		"0000000022200000000000000000000000000000000000000000000000001000",
		"0000000000000000000000000000000000000000000000000000000000101000",
		"0000000b0000000000000000000000000000000b000000000000000010101000",
		"1111111111111111111110001111111111111111111111111111100111111111",
		"1111111111111111111110001111111111111111111111111111100111111111"
	};
public :
	vector<vector<GameTile* >> tiles;
	int gridLength;
	GameWorld(Player*);
	void draw(RenderWindow&);
};


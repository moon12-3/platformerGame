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
	void setUpTiles();	// tile texture설정
	void createMap(std::string);	
	char tileType;	// tile의 type 임시 보관 변수
	Enemy goomba= Enemy(800, 100);
	int i;
	int a, b;
	std::vector<std::string> lines;
	Player* p;	// player 정보 가져오기
	vector<Enemy> goombas;
	string tile[H] = {	// 맵 그리기
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		"00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		"000000000000000000000000000000000c00000000000000000000000c000000000000000000000000000000000000000c00000000000000000000000c000000",
		"00000000000000c0000000000000000000000000000000c0000000000000000000000000000000c0000000000000000000000000000000c00000000000000000",
		"0000c00000000000000000c000000000000000000000000000000000000000000000c00055555550000555500000000000000000000055500005555000000000",
		"00000000000000000000000000000000000000000000000000005000000000000000000000000000000000000000000000000000000000000000000000000000",
		"00000000000000000000000000000000000000000000030000000000000000000000055500000000000000000000000000000000000000000000000000000000",
		"00000000000000000000000055555000000000300000020000000000000000000000000000000000000000500000000000055000050000000000550000000000",
		"00000000000000000000000000000000030000200000020000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		"9000000b000000000000000b00000000020000200000020000000000009900000000000b000009090000000b0000000000000000000000000000000000990000",
		"11111111111111111111111111111111111111111111111111111111110011111111111111111000111111111111111111111111111111111111111111001111",
		"11111111111111111111111111111111111111111111111111111111110011111111111111111000111111111111111111111111111111111111111111001111"
	};
public :
	void createEnemy();	// enemy 생성
	vector<vector<GameTile* >> tiles;
	int gridLength;
	GameWorld(Player*);
	void draw(RenderWindow&);
};


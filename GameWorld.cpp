#include "GameWorld.hpp"

using namespace sf;
using namespace std;

GameWorld::GameWorld(Player* p) {
	this->p = p;
	// setUpInitialState();
	setUpTiles();
	// createMap("Resources/Map/map1.png");
}

void GameWorld::setUpInitialState() {
	exitPos = Vector2i(W-2, H-2);
}

void GameWorld::setUpEnemyPositions() {
	enemyPos.clear();
	enemyPos.push_back(Vector2i(0, 2));
}

void GameWorld::setUpTiles() {
	tiles.clear();
	vector<GameTile*> row;
	for (int i = 0; i < H; i++) {
		row.clear();
		for (int j = 0; j < W; j++) {
			//tileType = lines.at(i)[j];
			tileType = tile[i][j];
			GameTile* tile = new GameTile("Resources/Images/Map.png", CELL_SIZE * j, CELL_SIZE * i, tileType);
			row.push_back(tile);
		}
		tiles.push_back(row);
	}
}

void GameWorld::draw(RenderWindow& app)
{
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			app.draw(tiles[i][j]->block);
			Collider c = p->getCollider();
			if (p->sprite.getGlobalBounds().intersects(tiles[i][j]->getGlobalBounds()) && !(tiles[i][j]->tileType == '0')) {
				tiles[i][j]->GetCollider().CheckCollision(c, 1.0f);
				p->onGround = true;
				p->isJumping = false;
			}
		}
	}
}

void GameWorld::createMap(string path)
{
	lines = vector<string>();
	ifstream file(path);

	string line;
	string currentLine;

	if (file.is_open()) {
		while (getline(file, line)) {
			lines.push_back(line);
			cout << line << endl;
		}
		file.close();
	}
	else {
		cout << "Unable to open file";
	}
}

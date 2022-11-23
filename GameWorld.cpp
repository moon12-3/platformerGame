#include "GameWorld.hpp"

using namespace sf;
using namespace std;

GameWorld::GameWorld(Player* p) {
	this->p = p;
	// setUpInitialState();
	setUpTiles();
	// createMap("Resources/Map/map1.png");
}

void GameWorld::setUpTiles() {
	tiles.clear();
	vector<GameTile*> row;
	for (int i = 0; i < H; i++) {
		row.clear();
		for (int j = 0; j < W; j++) {
			//tileType = lines.at(i)[j];
			tileType = tile[i][j];
			GameTile* tile;
			//if ((tiles[i][j]->tileType == '0')) tile = new GameTile();
			//else 
			tile = new GameTile("Resources/Images/Map.png", CELL_SIZE * j, CELL_SIZE * i, tileType);
			row.push_back(tile);
		}
		tiles.push_back(row);
	}
}

void GameWorld::draw(RenderWindow& app)
{
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if ((tiles[i][j]->tileType == '0')) continue;
			app.draw(tiles[i][j]->block);
			Collider c = p->getCollider();
			Vector2f direction;
			if (p->sprite.getGlobalBounds().intersects(tiles[i][j]->getGlobalBounds()) && !(tiles[i][j]->tileType == '0') && !(tiles[i][j]->tileType >= 'a')) {
				if (tiles[i][j]->GetCollider().CheckCollision(c, direction, 1.0f))
					p->onCollision(direction);
				// tiles[i][j]->GetCollider().CheckCollision(c, 1.0f);
				if (p->sprite.getPosition().y < tiles[i][j]->block.getPosition().y - 40) {
					p->onGround = true;
					p->isJumping = false;
				}
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

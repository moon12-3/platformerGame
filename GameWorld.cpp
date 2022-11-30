#include "GameWorld.hpp"

using namespace sf;
using namespace std;

GameWorld::GameWorld(Player* p) {
	this->p = p;
	i = 0;
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
			tileType = tile[i][j];
			GameTile* tile;
			if (tileType == '0')
				tile = new GameTile();
			else 
				tile = new GameTile("Resources/Images/Map.png", CELL_SIZE * j, CELL_SIZE * i, tileType);
			row.push_back(tile);
		}
		tiles.push_back(row);
	}
}
9
void GameWorld::draw(RenderWindow& app)
{
	/*if (p->getPositionX() > 500 + 500 * i) {
		cout << "»ý¼º" << endl;
		Enemy e(700+500*i, 100);
		goombas.push_back(&e);
		i++;
	}*/
	Enemy goomba(800, 100);

	/*for(int i = 0; i < goombas.size(); i++)
		goombas[i]->draw(app);*/
	goomba.draw(app);
	int a = min(H, (int)p->getPositionX());
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if ((tiles[i][j]->tileType == '0')) continue;
			app.draw(tiles[i][j]->block);
			Collider c = p->getCollider();
			Vector2f direction;
			/*for (int i = 0; i < goombas.size(); i++) {
				Collider e = goombas[i]->getCollider();
				tiles[i][j]->GetCollider().CheckCollision(e, direction, 1.0f);
			}*/
			Collider e = goomba.getCollider();
			tiles[i][j]->GetCollider().CheckCollision(e, direction, 1.0f);
			if (p->sprite.getGlobalBounds().intersects(tiles[i][j]->getGlobalBounds()) && !(tiles[i][j]->tileType >= 'a')) {
				if (tiles[i][j]->GetCollider().CheckCollision(c, direction, 1.0f))
					//p->onCollision(direction);
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

#include "GameWorld.hpp"

using namespace sf;
using namespace std;

GameWorld::GameWorld(Player* p) {
	this->p = p;
	i = 0;
	goombas.push_back(goomba);
	// setUpInitialState();
	setUpTiles();
	// createMap("Resources/Map/map1.png");
}

void GameWorld::setUpTiles() {
	tiles.clear();
	vector<GameTile*> row;	// ���� Ÿ�� ���� �迭
	for (int i = 0; i < H; i++) {	// ���� ���� ���� ũ�⸸ŭ �ݺ�
		row.clear();	// ���� ��Ҵ� ���� ����
		for (int j = 0; j < W; j++) {	// ���� ���� ���� ũ�⸸ŭ �ݺ�
			tileType = tile[i][j];	// string������ ���� ���
			GameTile* tile;
			if (tileType == '0')	// �����̶�� �� �� �ֱ�
				tile = new GameTile();
			else // �ƴ϶�� sprite ����
				tile = new GameTile("Resources/Images/Map.png", CELL_SIZE * j, CELL_SIZE * i, tileType);
			row.push_back(tile);	// Ÿ�� ���
		}
		tiles.push_back(row);	// ��ü ���� Ÿ�� ���
	}
}

void GameWorld::createEnemy()
{
	if (p->getPositionX() > 500 + 800 * i) {	// player�� Ư�� ��ġ�� �����ϸ� Enemy ����
		Enemy e = Enemy(1200 + 800 * i, 100);
		goombas.push_back(e);	// �迭�� ����ֱ�
		i++;
	}
}

void GameWorld::draw(RenderWindow& app)
{
	a = min(W, (int)p->getPositionX() / 50 + 16);
	b = max(0, (int)(p->getPositionX() / 50 - 16));
	// cout << a << ", " << b << ", " << p->getPositionX() << endl;
	for (int i = 0; i < H; i++) {
		for (int j = b; j < a; j++) {
			if ((tiles[i][j]->tileType == '0')) continue;	// ������ ä���� �ʰ�
			app.draw(tiles[i][j]->block);
			Collider c = p->getCollider();	// player Collider(�浹ü)
			Vector2f direction;
			if (!(tiles[i][j]->tileType >= 'a')) {
				for (int z = 0; z < goombas.size(); z++) {	// ������ ����ŭ �ݺ�
					if (goombas[z].sprite.getGlobalBounds().intersects(tiles[i][j]->getGlobalBounds())) {	// �� ��ϰ� ���� �ε��� ���
						Collider e = goombas[z].getCollider();
						tiles[i][j]->GetCollider().CheckCollision(e, direction, 1.0f); // ��, �Ʒ�, ������, ���������� ���� ������
						if (tiles[i][j]->block.getPosition().y < goombas[z].sprite.getPosition().y + 10) {
							if (goombas[z].sprite.getPosition().x < tiles[i][j]->block.getPosition().x + 52 && goombas[z].direction == 1)// enemy�� ���ʸ��� ���� ���
								goombas[z].direction = -1;
							else if (goombas[z].sprite.getPosition().x + 52 > tiles[i][j]->block.getPosition().x && goombas[z].direction == -1)	// �����ʸ�
								goombas[z].direction = 1;
						}
					}
				}
				if (p->sprite.getGlobalBounds().intersects(tiles[i][j]->getGlobalBounds()) && !p->dead && !(tiles[i][j]->tileType == '9')) {	// �� ��ϰ� player�� �ε��� ���
					tiles[i][j]->GetCollider().CheckCollision(c, direction, 1.0f);	// ��, �Ʒ�, ������, ���������� ���� ������
					if (p->sprite.getPosition().y < tiles[i][j]->block.getPosition().y - 40) {	// �ٴڸ鿡 ���� ���
						p->onGround = true;
						p->isJumping = false;	// �ٽ� ���� Ȱ��ȭ
					}
				}
			}
		}
	}
	Vector2f direction;
	for (int z = 0; z < goombas.size(); z++) {	// ������ ����ŭ �ݺ�
		if (goombas[z].sprite.getGlobalBounds().intersects(p->sprite.getGlobalBounds())) {	// �÷��̾�� ���� �ε��� ���
			if (!p->dead && !goombas[z].dead) {	// �÷��̾� �Ǵ� ���� ���� ���� ���
				Collider e = goombas[z].getCollider();
				p->getCollider().CheckCollision(e, direction, 1.0f);
			}	
			if (p->sprite.getPosition().y < goombas[z].sprite.getPosition().y - 45 && !p->dead) {
				goombas[z].dead = true;	// �Ӹ��� ������ enemy ���
				cout << z << endl;
			}
			else if(!goombas[z].dead) p->dead = true;	// �÷��̾� ���
		}
		for (int i = 0; i < goombas.size(); i++) {	// ������ ����ŭ �ݺ�
			if (goombas[i].sprite.getGlobalBounds().intersects(goombas[z].sprite.getGlobalBounds()) && z!=i && !goombas[i].dead && !goombas[z].dead) {	// ���� ���� �ε��� ���
				Collider e = goombas[i].getCollider();
				goombas[z].getCollider().CheckCollision(e, direction, 1.0f); // ��, �Ʒ�, ������, ���������� ���� ������
				if (goombas[z].sprite.getPosition().y < goombas[i].sprite.getPosition().y + 10) {
					if (goombas[i].getPosition().x < goombas[z].getPosition().x + 52 && goombas[i].direction == 1) {// enemy�� ���ʸ��� ���� ���
						cout << z << endl;
						goombas[i].direction = -1;
						goombas[z].direction = 1;
					}
					else if (goombas[i].getPositionX() + 52 > goombas[z].getPositionX() && goombas[i].direction == -1) {// �����ʸ�
						goombas[i].direction = 1;
						goombas[z].direction = -1;
						cout << z << endl;
					}
				}
			}
		}


	}
	for (int i = 0; i < goombas.size(); i++)
		if(b*50<=goombas[i].getPositionX() && a*50>= goombas[i].getPositionX())
			goombas[i].draw(app);
	if (p->deathScreen)	// ��ũ�� ���� ���� �� ���� �ʱ�ȭ
	{
		i = 0;
		goombas.clear();
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

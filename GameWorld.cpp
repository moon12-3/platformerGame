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
	vector<GameTile*> row;	// 가로 타일 담을 배열
	for (int i = 0; i < H; i++) {	// 게임 맵의 세로 크기만큼 반복
		row.clear();	// 전에 담았던 내용 삭제
		for (int j = 0; j < W; j++) {	// 게임 맵의 가로 크기만큼 반복
			tileType = tile[i][j];	// string변수의 숫자 담기
			GameTile* tile;
			if (tileType == '0')	// 공백이라면 빈 값 주기
				tile = new GameTile();
			else // 아니라면 sprite 설정
				tile = new GameTile("Resources/Images/Map.png", CELL_SIZE * j, CELL_SIZE * i, tileType);
			row.push_back(tile);	// 타일 담기
		}
		tiles.push_back(row);	// 전체 가로 타일 담기
	}
}

void GameWorld::createEnemy()
{
	if (p->getPositionX() > 500 + 800 * i) {	// player가 특정 위치에 도달하면 Enemy 생성
		Enemy e = Enemy(1200 + 800 * i, 100);
		goombas.push_back(e);	// 배열에 집어넣기
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
			if ((tiles[i][j]->tileType == '0')) continue;	// 공백은 채우지 않게
			app.draw(tiles[i][j]->block);
			Collider c = p->getCollider();	// player Collider(충돌체)
			Vector2f direction;
			if (!(tiles[i][j]->tileType >= 'a')) {
				for (int z = 0; z < goombas.size(); z++) {	// 생성된 적만큼 반복
					if (goombas[z].sprite.getGlobalBounds().intersects(tiles[i][j]->getGlobalBounds())) {	// 맵 블록과 적이 부딪힌 경우
						Collider e = goombas[z].getCollider();
						tiles[i][j]->GetCollider().CheckCollision(e, direction, 1.0f); // 위, 아래, 오른쪽, 왼쪽인지에 따라 막히게
						if (tiles[i][j]->block.getPosition().y < goombas[z].sprite.getPosition().y + 10) {
							if (goombas[z].sprite.getPosition().x < tiles[i][j]->block.getPosition().x + 52 && goombas[z].direction == 1)// enemy의 왼쪽면이 닿은 경우
								goombas[z].direction = -1;
							else if (goombas[z].sprite.getPosition().x + 52 > tiles[i][j]->block.getPosition().x && goombas[z].direction == -1)	// 오른쪽면
								goombas[z].direction = 1;
						}
					}
				}
				if (p->sprite.getGlobalBounds().intersects(tiles[i][j]->getGlobalBounds()) && !p->dead && !(tiles[i][j]->tileType == '9')) {	// 맵 블록과 player가 부딪힌 경우
					tiles[i][j]->GetCollider().CheckCollision(c, direction, 1.0f);	// 위, 아래, 오른쪽, 왼쪽인지에 따라 막히게
					if (p->sprite.getPosition().y < tiles[i][j]->block.getPosition().y - 40) {	// 바닥면에 닿은 경우
						p->onGround = true;
						p->isJumping = false;	// 다시 점프 활성화
					}
				}
			}
		}
	}
	Vector2f direction;
	for (int z = 0; z < goombas.size(); z++) {	// 생성된 적만큼 반복
		if (goombas[z].sprite.getGlobalBounds().intersects(p->sprite.getGlobalBounds())) {	// 플레이어와 적이 부딪힌 경우
			if (!p->dead && !goombas[z].dead) {	// 플레이어 또는 적이 죽지 않은 경우
				Collider e = goombas[z].getCollider();
				p->getCollider().CheckCollision(e, direction, 1.0f);
			}	
			if (p->sprite.getPosition().y < goombas[z].sprite.getPosition().y - 45 && !p->dead) {
				goombas[z].dead = true;	// 머리를 밟으면 enemy 사망
				cout << z << endl;
			}
			else if(!goombas[z].dead) p->dead = true;	// 플레이어 사망
		}
		for (int i = 0; i < goombas.size(); i++) {	// 생성된 적만큼 반복
			if (goombas[i].sprite.getGlobalBounds().intersects(goombas[z].sprite.getGlobalBounds()) && z!=i && !goombas[i].dead && !goombas[z].dead) {	// 적과 적이 부딪힌 경우
				Collider e = goombas[i].getCollider();
				goombas[z].getCollider().CheckCollision(e, direction, 1.0f); // 위, 아래, 오른쪽, 왼쪽인지에 따라 막히게
				if (goombas[z].sprite.getPosition().y < goombas[i].sprite.getPosition().y + 10) {
					if (goombas[i].getPosition().x < goombas[z].getPosition().x + 52 && goombas[i].direction == 1) {// enemy의 왼쪽면이 닿은 경우
						cout << z << endl;
						goombas[i].direction = -1;
						goombas[z].direction = 1;
					}
					else if (goombas[i].getPositionX() + 52 > goombas[z].getPositionX() && goombas[i].direction == -1) {// 오른쪽면
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
	if (p->deathScreen)	// 스크린 띄우고 있을 때 몬스터 초기화
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

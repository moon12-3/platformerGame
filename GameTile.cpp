#include "GameTile.hpp"

using namespace sf;

GameTile::GameTile(std::string textureName, float x, float y, char tileType) {
	this->tileType = tileType;
	block.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
	setUpSprite(textureName);
	pos = Vector2f(x, y);
	block.setPosition(pos);
	//block.setOrigin(Vector2f(CELL_SIZE, CELL_SIZE)/2.0f);
}

GameTile::GameTile()
{}

void GameTile::setUpSprite(std::string textureName)
{
	texture.loadFromFile(textureName);
	texture.setSmooth(true);
	block.setTexture(&texture);
	switch (tileType)
	{
	case '0' : 
		block.setTextureRect(IntRect(50, 0, 50, 50));
		break;
	case '1' :
		block.setTextureRect(IntRect(100, 0, 50, 50));
		break;
	case '2' :
		block.setTextureRect(IntRect(0, 0, 50, 50));
		break;
	case 'a' :
		block.setTextureRect(IntRect(50, 50, 100, 50));
		block.setSize(Vector2f(CELL_SIZE * 2, CELL_SIZE));
		break;
	case 'b' :
		block.setTextureRect(IntRect(200,0, 150, 50));
		block.setSize(Vector2f(CELL_SIZE * 3, CELL_SIZE));
		break;
	case 'c':
		block.setTextureRect(IntRect(350, 0, 150, 100));
		block.setSize(Vector2f(CELL_SIZE*3, CELL_SIZE*2));
		break;
	default:
		block.setTextureRect(IntRect(0, 100, 50, 50));
		break;
	}
	// std::cout << tileType << endl;
}




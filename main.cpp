#include"Player.hpp"
#include"DrawMap.hpp"
#include"Global.hpp"

using namespace sf;

Clock dtClock;
float dt;

void ResizeView(RenderWindow& app, View& view)	// 화면 크기 변경 시 조절
{
	float aspecRatio = float(app.getSize().x) / float(app.getSize().y);
	view.setSize(HEIGHT * aspecRatio, HEIGHT);
}

int main() {
	RenderWindow app(VideoMode(WIDTH, HEIGHT), "platformer");
	View view(Vector2f(0.0f, 0.0f), Vector2f(WIDTH, HEIGHT));
	app.setFramerateLimit(60);

	Texture map_texture;
	map_texture.loadFromFile("Resources/Images/block.png");
	//Sprite tile(map_texture);
	//tile.setPosition(CELL_SIZE, CELL_SIZE * 11);


	Sprite block[200];
	int n = 0; // 벽돌갯수
	for (int i = 10; i < 12; i++) {
		for (int j = 0; j < 16; j++) {
			block[n].setTexture(map_texture);
			block[n].setPosition(CELL_SIZE * j, CELL_SIZE * i);
			n++;
		}
	}

	Map map(HEIGHT / CELL_SIZE);

	Player player;

	DrawMap d;

	for (unsigned short a = 0; a < map.size(); a++) {	// 12
		for (unsigned short b = map[a].size() + 4; b < map[a].size(); b++) {	// 16
			map[a][b] = Cell::Wall;
		}
	}

	

	Font font;
	font.loadFromFile("Resources/Fonts/DungGeunMo.ttf");

	Text text("Hello Platformer!", font, 50);


	while (app.isOpen()) {
		Event e;
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
		view.setCenter(player.getPosition());

		app.clear(Color(98, 172, 255));
		// app.draw(tile);
		for (int i = 0; i < n; i++)
			app.draw(block[i]);
		// d.draw_map(app, map_texture, map);
		player.draw(app, n, block);

		app.display();

	} 
	return 0;
}

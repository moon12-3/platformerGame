#include "DrawMap.hpp"

using namespace sf;

DrawMap::DrawMap() {

}

void DrawMap::draw_map(RenderWindow& i_window, const Texture& i_map_texture, const Map& i_map) {
	Sprite cell_sprite(i_map_texture);
	for (unsigned short a = 0; a < i_map.size(); a++) {
		for (unsigned short b = 0; b < i_map[a].size(); b++) {
			if (Cell::Empty == i_map[a][b]) {
				continue;
			}

			cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);

			switch (i_map[a][b]) {
			case Cell::Wall : i_window.draw(cell_sprite);
			}
		}
	}
}

void DrawMap::draw(RenderWindow& i_window) {

}
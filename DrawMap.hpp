#include <array>
#include <chrono>

#include <SFML/Graphics.hpp>
#include "Global.hpp"

using namespace sf;

class DrawMap
{
public :
	DrawMap();
	void draw_map(RenderWindow& i_window, const sf::Texture& i_map_texture, const Map& i_map);
	void draw(RenderWindow& i_window);
};


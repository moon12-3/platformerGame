#pragma once

#include <chrono>
#include <vector>

#define WIDTH 800
#define HEIGHT 600
#define W 32
#define H 12

using namespace std;

constexpr unsigned char CELL_SIZE = 50;
constexpr unsigned char SCREEN_RESIZE = 2;

constexpr unsigned char SCREEN_HEIGHT = 600;
constexpr unsigned char SCREEN_WIDTH = 800;

constexpr chrono::microseconds FRAM_DURATION(16667);


enum Cell {
	Empty,
	Ground
};

typedef vector<std::array<Cell, SCREEN_HEIGHT / CELL_SIZE>> Map;



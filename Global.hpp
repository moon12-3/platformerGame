#pragma once

#include <chrono>
#include <vector>

#define WIDTH 800
#define HEIGHT 600
#define W 128
#define H 12
#define W_END W * 50 - WIDTH * 0.5

#define GRAVITY 8
#define SPEED 7

using namespace std;

constexpr unsigned char CELL_SIZE = 50;
constexpr unsigned char SCREEN_RESIZE = 2;

constexpr unsigned char SCREEN_HEIGHT = 600;
constexpr unsigned char SCREEN_WIDTH = 800;

constexpr chrono::microseconds FRAM_DURATION(16667);



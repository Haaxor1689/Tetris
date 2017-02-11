#pragma once

#include <chrono>
#include <SDL.h>
#include <map>
#include <sstream>
#include "Renderer.hpp"
#include "Enums.hpp"
#include "Event.hpp"
#include "Font.hpp"
#include "Grid.hpp"
#include "Tetromino.hpp"
#include "Sprite.hpp"

class Engine {
public:
	Engine();

	void run();

	void input(const Event& event);
	void step();
	void draw();
private:
	gameState state;

	Event event;
	Renderer renderer;

	unsigned score;
	unsigned lastScored;
	unsigned multiplier;

	Grid grid;
	Tetromino tetroFalling;
	Tetromino tetroWaiting;
	std::chrono::high_resolution_clock::time_point alarm;
};
#pragma once

#include <chrono>
#include "Renderer.hpp"
#include "Enums.hpp"
#include "Event.hpp"
#include "Grid.hpp"
#include "Tetromino.hpp"

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

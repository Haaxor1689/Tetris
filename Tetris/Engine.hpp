#pragma once

#include "Enums.hpp"
#include "Event.hpp"
#include "Grid.hpp"
#include "RenderController.hpp"
#include "Tetromino.hpp"
#include <chrono>

using Timer = std::chrono::high_resolution_clock::time_point;

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
	RenderController renderer;

	unsigned score;
	unsigned lastScored;
	unsigned multiplier;

	Grid grid;
	Tetromino tetroFalling;
	Tetromino tetroWaiting;
	Timer alarm;
};

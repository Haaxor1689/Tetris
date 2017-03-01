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

	// Main game loop
	void run();

	// All input handling function
	void input(const Event& event);

	// Game logic
	void step();

	// Game rendering
	void draw();
private:
	gameState state = gameState::intro;
	RenderController renderer;

	Grid grid; // hold all the information about playing grid
	Tetromino tetroFalling; // holds all the information about tetronimos
	Tetromino tetroWaiting;

	unsigned score = 0;
	unsigned lastScored = 0;
	unsigned multiplier = 0;
};

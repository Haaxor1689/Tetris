#pragma once

#include "Button.hpp"
#include "Enums.hpp"
#include "Event.hpp"
#include "Grid.hpp"
#include "RenderController.hpp"
#include "Tetromino.hpp"

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
	void bNewGame();

	gameState state = gameState::intro;
	RenderController renderer;

	Grid grid; // hold all the information about playing grid
	Tetromino tetromino; // holds all the information about tetronimos

	std::map<std::string, Button> buttons;

	unsigned score = 0;
	unsigned lastScored = 0;
	unsigned multiplier = 0;
};

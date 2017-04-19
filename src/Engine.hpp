#pragma once

#include "Button.hpp"
#include "Enums.hpp"
#include "Event.hpp"
#include "Grid.hpp"
#include "RenderController.hpp"
#include "Tetromino.hpp"

class Engine {
public:
	using ButtonMap = std::map<std::string, Button>;

	Engine();

	// Main game loop
	void run();

	template <gameState s>
	void loop() {
		Event event;
		while (event.poll())
			input<s>(event);
		step<s>();
		draw<s>();
	}

	// All input handling function
	template <gameState>
	void input(const Event& event) {}
	template <> void input<gameState::intro>(const Event& event);
	template <> void input<gameState::menu>(const Event& event);
	template <> void input<gameState::play>(const Event& event);
	template <> void input<gameState::gameover>(const Event& event);

	// Game logic
	template <gameState>
	void step() {}
	template <> void step<gameState::play>();

	// Game rendering
	template <gameState>
	void draw() {}
	template <> void draw<gameState::intro>();
	template <> void draw<gameState::menu>();
	template <> void draw<gameState::play>();
	template <> void draw<gameState::gameover>();

private:
	// Button functions
	void bNewGame();
	void bContinue();
	void bQuit();

	void addButton(std::string name,
	               Position pos,
	               unsigned width,
	               unsigned height,
	               void (Engine::* function)(),
	               int shortcut,
	               const std::string& font,
	               const std::string& sprite);

	gameState state = gameState::intro;
	RenderController renderer;

	Grid grid; // holds all the information about playing grid
	Tetromino tetromino; // holds all the information about tetronimos

	ButtonMap buttons;

	unsigned score = 0;
	unsigned lastScored = 0;
	unsigned multiplier = 0;
};
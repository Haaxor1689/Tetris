#ifndef TETRIS_ENGINE_HPP
#define TETRIS_ENGINE_HPP

#include <chrono>
#include <SDL.h>
#include <map>
#include <sstream>
#include "Renderer.hpp"
#include "Event.hpp"
#include "Font.hpp"
#include "Grid.hpp"
#include "Tetromino.hpp"
#include "Sprite.hpp"

enum class gameState {
	exit, intro, menu, play, pause
};

class Engine {
public:
	Engine();

	void run();

	void input(const Event& event);
	void step();
	void draw();

	~Engine();
private:
	void text(std::string text,
	          std::string font,
	          int x,
	          int y,
	          SDL_Color color = {255, 255, 255, 255},
	          textHAlign hAlign = textHAlign::middle,
	          textVAlign vAlign = textVAlign::middle);
	void sprite(std::string texture, int x, int y);

	gameState state;

	Event event;
	Renderer renderer;
	std::map<std::string, Sprite> textures;
	std::map<std::string, Font> fonts;

	unsigned score;
	unsigned multiplier;

	Grid grid;
	Tetromino tetroFalling;
	Tetromino tetroWaiting;
	std::chrono::high_resolution_clock::time_point alarm;
};


#endif //TETRIS_ENGINE_HPP

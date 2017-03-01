#pragma once

#include "Enums.hpp"
#include "Font.hpp"
#include "Position.hpp"
#include "Sprite.hpp"
#include "Wrappers.hpp"
#include <SDL/SDL.h>
#include <map>
#include <stdexcept>

class RenderController {
public:
	RenderController() {
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
		renderer = SDL_CreateRenderer(&window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	}

	void drawText(std::string text,
					  std::string font,
					  Position pos,
					  SDL_Color color = { 255, 255, 255, 255 },
					  textHAlign hAlign = textHAlign::Middle,
					  textVAlign vAlign = textVAlign::Middle) {
		fonts.find(font)->second.draw(&renderer, text, pos.x, pos.y, hAlign, vAlign, color);
	}

	void drawSprite(std::string texture,
						 Position pos,
						 int alpha = 255) {
		sprites.find(texture)->second.draw(&renderer, pos.x, pos.y, alpha);
	}

	void addFont(std::string name, std::string path, int size) {
		fonts.insert(make_pair(name, Font(path, size)));
	}

	void addSprite(std::string name, std::string path) {
		sprites.insert(make_pair(name, Sprite(path, &renderer)));
	}

	SDL_Renderer* getRenderer() const {
		return &renderer;
	}

private:
	Window window;
	Renderer renderer;
	std::map<std::string, Sprite> sprites;
	std::map<std::string, Font> fonts;
};

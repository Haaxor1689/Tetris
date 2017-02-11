#pragma once

#include <SDL.h>
#include <stdexcept>
#include "Sprite.hpp"
#include "Font.hpp"
#include "Enums.hpp"
#include "Position.hpp"
#include <map>

class Renderer {
public:
	Renderer() {
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
		if (!window)
			throw std::runtime_error(SDL_GetError());

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (!renderer)
			throw std::runtime_error(SDL_GetError());
	}

	~Renderer() {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
	}

	void drawText(std::string text,
					  std::string font,
					  Position pos,
					  SDL_Color color = { 255, 255, 255, 255 },
					  textHAlign hAlign = textHAlign::middle,
					  textVAlign vAlign = textVAlign::middle) {
		fonts.find(font)->second.draw(renderer, text, pos.x, pos.y, hAlign, vAlign, color);
	}

	void drawSprite(std::string texture,
						 Position pos,
						 int alpha = 255) {
		sprites.find(texture)->second.draw(renderer, pos.x, pos.y, alpha);
	}

	void addFont(std::string name, std::string path, int size) {
		fonts.insert(std::make_pair(name, Font(path, size)));
	}

	void addSprite(std::string name, std::string path) {
		sprites.insert(std::make_pair(name, Sprite(path, renderer)));
	}

	SDL_Renderer* getRenderer() const {
		return renderer;
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::map<std::string, Sprite> sprites;
	std::map<std::string, Font> fonts;
};

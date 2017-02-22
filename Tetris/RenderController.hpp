#pragma once

#include "Enums.hpp"
#include "Font.hpp"
#include "Position.hpp"
#include "Sprite.hpp"
#include <SDL.h>
#include <map>
#include <stdexcept>

struct Window {
	Window() {
		ptr = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
	}

	Window(const Window& other) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&& other) = delete;
	Window& operator=(Window&& other) = delete;

	~Window() {
		SDL_DestroyWindow(ptr);
	}

	SDL_Window* ptr;
};

struct Renderer {
	Renderer(Window& window, int arguments = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) {
		ptr = SDL_CreateRenderer(window.ptr, -1, arguments);
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
	}

	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;
	Renderer(Renderer&& other) = delete;
	Renderer& operator=(Renderer&& other) = delete;

	~Renderer() {
		SDL_DestroyRenderer(ptr);
	}

	SDL_Renderer* ptr;
};

class RenderController {
public:
	RenderController() : window(), renderer(window){}

	void drawText(std::string text,
					  std::string font,
					  Position pos,
					  SDL_Color color = { 255, 255, 255, 255 },
					  textHAlign hAlign = textHAlign::middle,
					  textVAlign vAlign = textVAlign::middle) {
		fonts.find(font)->second.draw(renderer.ptr, text, pos.x, pos.y, hAlign, vAlign, color);
	}

	void drawSprite(std::string texture,
						 Position pos,
						 int alpha = 255) {
		sprites.find(texture)->second.draw(renderer.ptr, pos.x, pos.y, alpha);
	}

	void addFont(std::string name, std::string path, int size) {
		fonts.insert(make_pair(name, Font(path, size)));
	}

	void addSprite(std::string name, std::string path) {
		sprites.insert(make_pair(name, Sprite(path, renderer.ptr)));
	}

	SDL_Renderer* getRenderer() const {
		return renderer.ptr;
	}

private:
	Window window;
	Renderer renderer;
	std::map<std::string, Sprite> sprites;
	std::map<std::string, Font> fonts;
};

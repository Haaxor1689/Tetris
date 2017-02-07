#ifndef TETRIS_RENDERER_HPP
#define TETRIS_RENDERER_HPP

#include <iostream>
#include <SDL.h>
#include <stdexcept>

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

	SDL_Window* window;
	SDL_Renderer* renderer;
};


#endif //TETRIS_RENDERER_HPP

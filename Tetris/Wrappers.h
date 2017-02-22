#pragma once

#include <SDL.h>

struct Surface {
	Surface(SDL_Surface* surface) : ptr(surface) {
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
	}
	Surface& operator=(SDL_Surface* surface) {
		ptr = surface;
		if (!ptr)
			throw std::runtime_error(SDL_GetError());

		return *this;
	}

	SDL_Surface* operator&() {
		return ptr;
	}

	~Surface() {
		SDL_FreeSurface(ptr);
	}

private:
	SDL_Surface* ptr;
};

struct Texture {
	Texture(SDL_Texture* texture) : ptr(texture) {
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
	}
	Texture& operator=(SDL_Texture* texture) {
		ptr = texture;
		if (!ptr)
			throw std::runtime_error(SDL_GetError());

		return *this;
	}

	SDL_Texture* operator&() {
		return ptr;
	}

	~Texture() {
		SDL_DestroyTexture(ptr);
	}
	
private:
	SDL_Texture* ptr;
};
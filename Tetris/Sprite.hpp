#ifndef TETRIS_SPRITE_HPP
#define TETRIS_SPRITE_HPP

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Renderer.hpp"

class Sprite {
public:
	Sprite(std::string path, Renderer& renderer) {
		SDL_Surface* loadedImage = IMG_Load(path.c_str());
		if (!loadedImage)
			throw std::runtime_error(SDL_GetError());

		texture = SDL_CreateTextureFromSurface(renderer.renderer, loadedImage);
		if (!texture)
			throw std::runtime_error(SDL_GetError());

		SDL_FreeSurface(loadedImage);
		SDL_QueryTexture(texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
	}

	Sprite(Sprite&& other) noexcept {
		rectangle = other.rectangle;
		texture = other.texture;
		other.texture = nullptr;
	}

	~Sprite() {
		SDL_DestroyTexture(texture);
	}

	void draw(Renderer& renderer, int x, int y, int alpha = 255) {
		rectangle.x = x;
		rectangle.y = y;

		if (alpha != 255)
			if (SDL_SetTextureAlphaMod(texture, alpha))
				throw std::runtime_error(SDL_GetError());

		if (SDL_RenderCopy(renderer.renderer, texture, nullptr, &rectangle))
			throw std::runtime_error(SDL_GetError());

		if (alpha != 255)
			if (SDL_SetTextureAlphaMod(texture, 255))
				throw std::runtime_error(SDL_GetError());
	}

private:
	SDL_Rect rectangle;
	SDL_Texture* texture;
};

#endif //TETRIS_SPRITE_HPP

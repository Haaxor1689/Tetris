#pragma once

#include "Wrappers.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite {
public:
	Sprite(std::string path, SDL_Renderer* renderer) {
		Surface loadedImage = IMG_Load(path.c_str());

		texture = SDL_CreateTextureFromSurface(renderer, &loadedImage);

		SDL_QueryTexture(&texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
	}

	Sprite(const Sprite& other) = delete;
	Sprite& operator=(const Sprite& other) = delete;

	Sprite(Sprite&& other) noexcept {
		rectangle = other.rectangle;
		texture = std::move(other.texture);
	}

	Sprite& operator=(Sprite&& other) noexcept {
		rectangle = other.rectangle;
		texture = std::move(other.texture);

		return *this;
	}

	~Sprite() = default;

	void draw(SDL_Renderer* renderer, int x, int y, int alpha = 255) {
		rectangle.x = x;
		rectangle.y = y;

		if (alpha != 255)
			if (SDL_SetTextureAlphaMod(&texture, alpha))
				throw std::runtime_error(SDL_GetError());

		if (SDL_RenderCopy(renderer, &texture, nullptr, &rectangle))
			throw std::runtime_error(SDL_GetError());

		if (alpha != 255)
			if (SDL_SetTextureAlphaMod(&texture, 255))
				throw std::runtime_error(SDL_GetError());
	}

private:
	SDL_Rect rectangle;
	Texture texture;
};

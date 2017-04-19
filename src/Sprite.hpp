#pragma once

#include "Wrappers.hpp"
#include <SDL.h>
#include <SDL_image.h>

class Sprite {
public:
	Sprite(std::string path, SDL_Renderer* renderer) {
		try {
			texture = IMG_LoadTexture(renderer, path.c_str());
		} catch (const std::exception& err) {
			throw std::runtime_error("Error while loading " + path + ": " + err.what());
		}
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

	void draw(SDL_Renderer* renderer, Position pos, Uint8 alpha = 255) {
		rectangle.x = pos.x;
		rectangle.y = pos.y;

		if (alpha != 255)
			if (SDL_SetTextureAlphaMod(&texture, alpha))
				throw std::runtime_error(SDL_GetError());

		if (SDL_RenderCopy(renderer, &texture, nullptr, &rectangle))
			throw std::runtime_error(SDL_GetError());

		if (alpha != 255)
			if (SDL_SetTextureAlphaMod(&texture, 255))
				throw std::runtime_error(SDL_GetError());
	}

	void draw(SDL_Renderer* renderer, SDL_Rect& bBox, Uint8 alpha = 255) {
		if (alpha != 255)
			if (SDL_SetTextureAlphaMod(&texture, alpha))
				throw std::runtime_error(SDL_GetError());

		if (SDL_RenderCopy(renderer, &texture, nullptr, &bBox))
			throw std::runtime_error(SDL_GetError());

		if (alpha != 255)
			if (SDL_SetTextureAlphaMod(&texture, 255))
				throw std::runtime_error(SDL_GetError());
	}

	int getWidth() const noexcept {
		return rectangle.w;
	}

	int getHeight() const noexcept {
		return rectangle.h;
	}

private:
	SDL_Rect rectangle;
	Texture texture;
};

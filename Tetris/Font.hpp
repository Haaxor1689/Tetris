#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include <string>
#include "Enums.hpp"

class Font {
public:
	Font(std::string path, int size) {
		font = TTF_OpenFont(path.c_str(), size);
		if (!font)
			throw std::runtime_error(SDL_GetError());
	}

	Font(Font&& other) {
		font = other.font;
		other.font = nullptr;
	}

	~Font() {
		TTF_CloseFont(font);
	}

	void draw(SDL_Renderer* renderer, std::string text, int x, int y, textHAlign hAlign, textVAlign vAlign, SDL_Color& color) {
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		if (!surface)
			throw std::runtime_error(SDL_GetError());

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (!texture)
			throw std::runtime_error(SDL_GetError());

		SDL_FreeSurface(surface);

		SDL_Rect rectangle;
		SDL_QueryTexture(texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
		rectangle.x = x;
		rectangle.y = y;

		switch(hAlign) {
		case textHAlign::left:
			rectangle.x = x;
			break;
		case textHAlign::middle:
			rectangle.x = x - rectangle.w / 2;
			break;
		case textHAlign::right:
			rectangle.x = x - rectangle.w;
			break;
		}

		switch(vAlign) {
		case textVAlign::top:
			rectangle.y = y;
			break;
		case textVAlign::middle:
			rectangle.y = y - rectangle.h / 2;
			break;
		case textVAlign::bottom:
			rectangle.y = y - rectangle.h;
			break;
		}

		if (SDL_RenderCopy(renderer, texture, nullptr, &rectangle))
			throw std::runtime_error(SDL_GetError());

		SDL_DestroyTexture(texture);
	}

private:
	TTF_Font* font;
};
#pragma once

#include "Enums.hpp"
#include "Wrappers.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdexcept>

class Text {
public:
	/**
	 * \brief Creates an instance of font from path to font file with given size
	 * \throw std::runtime_error if font fails to be created.
	 */
	Text(std::string path, int size) {
		font = TTF_OpenFont(path.c_str(), size);
	}

	Text(const Text& other) = delete;
	Text& operator=(const Text& other) = delete;

	Text(Text&& other) noexcept {
		rectangle = other.rectangle;
		font = std::move(other.font);
	}

	Text& operator=(Text&& other) noexcept {
		rectangle = other.rectangle;
		font = std::move(other.font);

		return *this;
	}

	/**
	 * \param renderer reference to renderer which should renderering target.
	 * \param text text string to be drawn.
	 * \param x x coordinate of textbox's pivot.
	 * \param y y coordinate of textbox's pivot.
	 * \param hAlign vertical alignment of text.
	 * \param vAlign horizontal alignment of text.
	 * \param color color of text in format { r, g, b, a }.
	 * \throw std::runtime_error if call to SDL_RenderCopy fails.
	 */
	void draw(SDL_Renderer* renderer, std::string text, int x, int y, textHAlign hAlign, textVAlign vAlign, SDL_Color& color) {
		surface = TTF_RenderText_Solid(&font, text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(renderer, &surface);
		
		SDL_QueryTexture(&texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
		rectangle.x = x;
		rectangle.y = y;

		switch (hAlign) {
		case textHAlign::Left:
			rectangle.x = x;
			break;
		case textHAlign::Middle:
			rectangle.x = x - rectangle.w / 2;
			break;
		case textHAlign::Right:
			rectangle.x = x - rectangle.w;
			break;
		}

		switch (vAlign) {
		case textVAlign::Top:
			rectangle.y = y;
			break;
		case textVAlign::Middle:
			rectangle.y = y - rectangle.h / 2;
			break;
		case textVAlign::Bottom:
			rectangle.y = y - rectangle.h;
			break;
		}

		if (SDL_RenderCopy(renderer, &texture, nullptr, &rectangle))
			throw std::runtime_error(SDL_GetError());
	}

private:
	SDL_Rect rectangle;
	Surface surface;
	Texture texture;
	Font font;
};

#pragma once

#include "Enums.hpp"
#include "Wrappers.hpp"
#include <SDL_FontCache.h>
#include <stdexcept>

class Text {
public:
	/**
	 * \brief Creates an instance of font from path to font file with given size
	 * \throw std::runtime_error if font fails to be created.
	 */
	Text(SDL_Renderer* renderer, std::string path, int size, SDL_Color& color) {
		font = FC_CreateFont();
		FC_LoadFont(&font, renderer, path.c_str(), size, color, TTF_STYLE_NORMAL);
	}

	Text(const Text& other) = delete;
	Text& operator=(const Text& other) = delete;

	Text(Text&& other) noexcept {
		rectangle = other.rectangle;
		surface = std::move(other.surface);
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
	 * \param pos position of textbos's pivot
	 * \param hAlign vertical alignment of text.
	 * \param vAlign horizontal alignment of text.
	 * \throw std::runtime_error if call to SDL_RenderCopy fails.
	 */
	void draw(SDL_Renderer* renderer, std::string text, Position pos, horizontalAlign hAlign, verticalAlign vAlign) {
		FC_AlignEnum align = FC_ALIGN_RIGHT;
		switch (hAlign) {
		case horizontalAlign::Left:
			align = FC_ALIGN_LEFT;
			break;
		case horizontalAlign::Middle:
			align = FC_ALIGN_CENTER;
			break;
		case horizontalAlign::Right:
			break;
		}

		switch (vAlign) {
		case verticalAlign::Top:
			pos.y -= FC_GetLineHeight(&font) / 2;
			break;
		case verticalAlign::Middle:
			break;
		case verticalAlign::Bottom:
			pos.y += FC_GetLineHeight(&font) / 2;
			break;
		}

		FC_DrawAlign(&font, renderer, static_cast<float>(pos.x), static_cast<float>(pos.y), align, text.c_str());

	}

private:
	SDL_Rect rectangle;
	Surface surface;
	Font font;
};

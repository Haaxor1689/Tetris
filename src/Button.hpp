#pragma once

#include "Event.hpp"
#include "Position.hpp"
#include "RenderController.hpp"
#include <functional>

class Engine;

class Button {
public:
	Button(const std::string& text,
	       Position pos,
	       unsigned width,
	       unsigned height,
	       std::function<void()> action,
	       int shortcut,
	       const std::string& font,
	       const std::string& sprite = "")
		: text(text),
		  pivot(pos),
		  action(action),
		  shortcut(shortcut),
		  font(font),
		  sprite(sprite) {
		bounds.w = width;
		bounds.h = height;
		bounds.x = pos.x - width / 2;
		bounds.y = pos.y - height / 2;
	}

	void input(const Event& event) {
		switch (event.getType()) {
			case eventType::KeyDown:
				if (event.getKey() == shortcut)
					action();
				break;
			case eventType::MouseButtonUp:
				if (event.getPosition().isInside(bounds))
					action();
				break;
			default: break;
		}
	}

	void draw(RenderController& renderer) {
		if (sprite != "")
			renderer.drawSprite(sprite, bounds);
		if (font != "")
			renderer.drawText(text, font, pivot, verticalAlign::Top);
	}

private:
	std::string text;
	Position pivot;
	SDL_Rect bounds;
	std::function<void()> action;
	int shortcut;
	std::string font;
	std::string sprite;
};

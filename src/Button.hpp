#pragma once

#include "Event.hpp"
#include "Position.hpp"
#include "RenderController.hpp"
#include <functional>

class Engine;

class Button {
public:
	Button(Position pos,
			 int width,
			 int height,
			 const std::string& text = "",
			 const std::string& font = "",
			 const std::string& sprite = "_None",
			 std::function<void()> action = []() {},
			 int shortcut = SDLK_UNKNOWN) : pivot(pos),
													  text(text),
													  font(font),
													  sprite(sprite),
													  action(action),
													  shortcut(shortcut) {
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
		if (sprite != "_None")
			renderer.drawSprite(sprite, { bounds.x, bounds.y });
		if (text != "")
			renderer.drawText(text, font, pivot);
	}

private:
	Position pivot;
	SDL_Rect bounds;
	std::string text;
	std::string font;
	std::string sprite;
	std::function<void()> action;
	int shortcut;
};

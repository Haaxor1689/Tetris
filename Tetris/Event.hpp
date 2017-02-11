#pragma once

#include <SDL.h>
#include <stdexcept>
#include <typeinfo>

class Event {
public:
	auto type() const {
		return event.type;
	}

	auto key() const {
		if (event.type == SDL_KEYDOWN) {
			return event.key.keysym.sym;
		}
		throw std::logic_error("Not a key.");
	}

	SDL_Event& get() { return event; }

private:
	SDL_Event event;
};
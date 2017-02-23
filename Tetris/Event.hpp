#pragma once

#include <SDL.h>
#include <stdexcept>
#include "Position.hpp"

class Event {
public:
	int type() const {
		return event.type;
	}

	std::string name() const {
		switch (type()) {
		case SDL_KEYDOWN: return "KeyDown";
		case SDL_KEYUP: return "KeyUp";
		case SDL_MOUSEMOTION: return "MouseMotion";
		case SDL_MOUSEBUTTONDOWN: return "MouseButtonDown";
		case SDL_MOUSEBUTTONUP: return "MouseButtonUp";
		default: return "Unused";
		}
	}

	int key() const {
		switch(type()) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			return event.key.keysym.sym;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			return event.button.button;
		default:
			throw std::logic_error("No key for " + name() + " event.");
		}
	}

	int state() const {
		switch (type()) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			return event.key.state;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			return event.button.state;
		default:
			throw std::logic_error("No state for " + name() + " event.");
		}
	}

	Position position() const {
		switch (type()) {
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			return { event.button.x, event.button.y };
		default:
			throw std::logic_error("No position for " + name() + " event.");
		}
		
	}

	SDL_Event* operator&() {
		return &event;
	}

private:
	SDL_Event event;
};

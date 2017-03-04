#pragma once

#include <SDL.h>
#include <stdexcept>
#include "Enums.hpp"
#include "Position.hpp"

class Event {
public:
	Event() = default;

	/**
	 * \brief Polls SDL's event queue and if there is pending event dequeues it. Replaces previous event.
	 * \return True if there was an pending event
	 */
	bool poll() {
		if (SDL_PollEvent(&event)) {
			type = toEventType(event.type);
			return true;
		}
		return false;
	}

	/**
	 * \return Type of actual event.
	 */
	eventType getType() const {
		return type;
	}

	/**
	 * \brief Applies to: KeyDown/Up, MouseButtonDown/Up
	 * \throw std::logic_error if key doesn't apply to current event's type
	 * \return If event type is KeyDown/Up, returns keyboard key, or if event type is MouseButtonUp/Down returns mouse key.
	 */
	int getKey() const {
		switch(type) {
		case eventType::KeyDown:
		case eventType::KeyUp:
			return event.key.keysym.sym;
		case eventType::MouseButtonDown:
		case eventType::MouseButtonUp:
			return event.button.button;
		default:
			throw std::logic_error("No key for " + toString(type) + " event.");
		}
	}

	/**
	 * \brief Applies to: KeyDown/Up, MouseButtonDown/Up
	 * \throw std::logic_error: if state doesn't apply to current event's type
	 * \return State of current event, e.g. pressed or released
	 */
	int getState() const {
		switch (type) {
		case eventType::KeyDown:
		case eventType::KeyUp:
			return event.key.state;
		case eventType::MouseButtonDown:
		case eventType::MouseButtonUp:
			return event.button.state;
		default:
			throw std::logic_error("No state for " + toString(type) + " event.");
		}
	}

	/**
	* \brief Applies to: MouseButtonDown/Up
	* \throw std::logic_error: if position doesn't apply to current event's type
	* \return Positon where current event happened.
	*/
	Position getPosition() const {
		switch (type) {
		case eventType::MouseButtonDown:
		case eventType::MouseButtonUp:
			return { event.button.x, event.button.y };
		default:
			throw std::logic_error("No position for " + toString(type) + " event.");
		}
		
	}

private:
	eventType type;
	SDL_Event event;
};

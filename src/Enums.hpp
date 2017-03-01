#pragma once
#include <string>

/**
 * \brief Holds information about current game state.
 */
enum class gameState {
	exit, intro, menu, play, gameover
};

/**
 * \brief Holds information about which block to draw. Each color corresponds to a tetroType and can be casted into this type.
 */
enum class gridBlock {
	Empty, Blue, Green, Orange, Purple, Red, Teal, Yellow
};

/**
 * \brief All the diffrent types of tetronimo represented by letters. Each type corresponds to a gridBlock and can be casted into this type.
 */
enum class tetroType {
	None, I, O, T, J, L, S, Z
};

enum class tetroState {
	Disabled, Falling, Waiting
};

/**
 * \brief Sets horizontal align of text. 
 */
enum class textHAlign {
	Left, Middle, Right
};

/**
 * \brief Sets vertical align of text.
 */
enum class textVAlign {
	Top, Middle, Bottom
};

/**
 * \brief Enums for all suppoted SDL_Events.
 */
enum class eventType {
	KeyDown, KeyUp, MouseMotion, MouseButtonDown, MouseButtonUp, Quit, Unused
};

gridBlock toGridBlock(tetroType value);
eventType toEnumType(int value);

std::string toString(tetroType value);
std::string toString(gridBlock value);
std::string toString(eventType value);
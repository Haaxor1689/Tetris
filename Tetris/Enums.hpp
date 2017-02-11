#pragma once
#include <string>

enum class gameState {
	exit, intro, menu, play, gameover
};

enum class gridBlock {
	Empty, Blue, Green, Orange, Purple, Red, Teal, Yellow
};

enum class tetroType {
	None, I, O, T, J, L, S, Z
};

enum class tetroState {
	Disabled, Falling, Waiting
};

enum class textHAlign {
	left, middle, right
};

enum class textVAlign {
	top, middle, bottom
};

gridBlock toGridBlock(tetroType value);
std::string toString(tetroType value);
std::string toString(gridBlock value);
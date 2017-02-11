#pragma once

struct Position {
	Position() : x(0),
					 y(0) {
	}

	Position(int x, int y) : x(x),
									 y(y) {
	}

	Position(const Position& other) = default;

	Position& operator=(const Position& other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	int x;
	int y;
};

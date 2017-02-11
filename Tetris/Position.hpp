#pragma once

struct Position {
	Position() : x(0),
					 y(0) {
	}

	Position(int x, int y) : x(x),
									 y(y) {
	}

	Position(const Position& other) : x(other.x),
												 y(other.y) {
	}

	void operator=(const Position& other) {
		x = other.x;
		y = other.y;
	}

	int x;
	int y;
};

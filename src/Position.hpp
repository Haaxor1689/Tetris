#pragma once

struct Position {
	Position() = default;
	Position(int x, int y) : x(x), y(y) {}
	Position(const Position& other) = default;
	Position& operator=(const Position& other) = default;
	Position(Position&& other) noexcept = default;
	Position& operator=(Position&& other) noexcept = default;
	~Position() = default;

	int x = 0;
	int y = 0;
};

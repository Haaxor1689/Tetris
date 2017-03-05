#pragma once

struct Position {
	Position() = default;
	Position(int x, int y) : x(x), y(y) {}
	Position(const Position& other) = default;
	Position& operator=(const Position& other) = default;
	Position(Position&& other) noexcept = default;
	Position& operator=(Position&& other) noexcept = default;
	~Position() = default;

	Position& operator+=(const Position& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	friend Position operator+(const Position& lhs, const Position& rhs) {
		return { lhs.x + rhs.x, lhs.y + rhs.y };
	}

	Position& operator-=(const Position& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	friend Position operator-(const Position& lhs, const Position& rhs) {
		return{ lhs.x - rhs.x, lhs.y - rhs.y };
	}

	bool isInside(const SDL_Rect& rectangle) const noexcept{
		return x >= rectangle.x && y >= rectangle.y && x <= rectangle.x + rectangle.w && y <= rectangle.y + rectangle.h;
	}

	int x = 0;
	int y = 0;
};

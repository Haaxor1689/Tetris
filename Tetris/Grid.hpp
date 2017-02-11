#pragma once

#include "Enums.hpp"
#include "Position.hpp"
#include <array>
#include <deque>

struct Grid {
	Grid(Position corner, int tileSize) : corner(corner),
													  tileSize(tileSize),
													  width(10),
													  height(20) {
		for (auto& i : matrix)
			i.fill(gridBlock::Empty);
	}

	void reset() {
		for (auto& i : matrix)
			i.fill(gridBlock::Empty);
		done.clear();
	}

	bool isEmpty(Position&& pos) const {
		return matrix[pos.y][pos.x] == gridBlock::Empty;
	}

	const Position corner;
	const int tileSize;
	const int width;
	const int height;
	std::array<std::array<gridBlock, 10>, 20> matrix;
	std::deque<std::array<gridBlock, 10>> done;
};

#pragma once

#include "Enums.hpp"
#include "Position.hpp"
#include <array>
#include <deque>

struct Grid {
	Grid(Position corner, int tileSize) : corner(corner),
													  tileSize(tileSize) {
		for (auto& i : matrix)
			i.fill(gridBlock::Empty);
	}

	void reset() {
		for (auto& i : matrix)
			i.fill(gridBlock::Empty);
		done.clear();
	}

	bool isEmpty(Position&& pos) const noexcept {
		return matrix[pos.y][pos.x] == gridBlock::Empty;
	}

	const Position corner;
	const int tileSize;
	const int width = 10;
	const int height = 20;
	std::array<std::array<gridBlock, 10>, 20> matrix;
	std::deque<std::array<gridBlock, 10>> done;
};

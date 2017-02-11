#pragma once

#include <array>
#include <deque>
#include "Enums.hpp"
#include "Position.hpp"

struct Grid {
	Grid (Position corner, int tileSize) : corner(corner),
	                                       tileSize(tileSize),
	                                       width(static_cast<int>(matrix[0].size())),
	                                       height(static_cast<int>(matrix.size())) {
		for(auto& i : matrix)
			i.fill(gridBlock::Empty);
	}

	void reset() {
		for (auto& i : matrix)
			i.fill(gridBlock::Empty);
	}

	bool isEmpty(Position&& pos) const {
		return matrix[pos.y][pos.x] == gridBlock::Empty;
	}

	const Position corner;
	const int tileSize;
	const int width;
	const int height;
	std::array<std::array<gridBlock, 10>, 20> matrix;
	std::deque<std::array<gridBlock, 10> > done;
};

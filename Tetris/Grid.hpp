#ifndef TETRIS_GRID_HPP
#define TETRIS_GRID_HPP

#include <array>
#include "Position.hpp"

enum class gridBlock {
	Empty, Blue, Green, Orange, Purple, Red, Teal, Yellow
};

struct Grid {
	Grid (Position corner, int tileSize) : corner(corner),
	                                       tileSize(tileSize),
	                                       width(static_cast<int>(matrix[0].size())),
	                                       height(static_cast<int>(matrix.size())) {
		for(auto& i : matrix)
			i.fill(gridBlock::Empty);
	}

	const Position corner;
	const int tileSize;
	const int width;
	const int height;
	std::array<std::array<gridBlock, 10>, 20> matrix;
};

#endif //TETRIS_GRID_HPP

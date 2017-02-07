#ifndef TETRIS_TETROMINO_HPP
#define TETRIS_TETROMINO_HPP

#include <map>
#include <chrono>
#include "Event.hpp"
#include "Grid.hpp"
#include "Position.hpp"
#include "Sprite.hpp"

enum class tetroType {
	None, I, O, T, J, L, S, Z
};

enum class tetroState {
	Disabled, Falling, Waiting
};

class Tetromino {
public:
	Tetromino(Grid& grid);

	void input(const Event& event);
	void step();
	void draw(Renderer& renderer, std::map<std::string, Sprite>& textures);

	void setState(tetroState newState);
	tetroState getState() const;

	void setType();
	void setType(tetroType type);
	tetroType getType() const;

	void resetPosition();

	bool nonCollision(Position pos);

	bool rotateLeft();
	bool rotateRight();
	void setGround();
	void drop();

private:
	Grid& grid;
	Position pivot;
	Position ground;
	tetroType type;
	tetroState state;
	int worth;

	std::array<Position, 4> blocks;
	std::chrono::high_resolution_clock::time_point alarm;
	std::string texture;
};

#endif //TETRIS_TETROMINO_HPP

#pragma once

#include "Enums.hpp"
#include "Event.hpp"
#include "Grid.hpp"
#include "Renderer.hpp"
#include <chrono>

class Tetromino {
public:
	explicit Tetromino(Grid& grid);

	void input(const Event& event);
	void step();
	void draw(Renderer& renderer);

	void setState(tetroState newState);
	tetroState getState() const;

	void setType();
	void setType(tetroType newType);
	tetroType getType() const;

	void setStepSpeed(float speed);

	int getWorth() const;
	bool resetPosition();

	bool nonCollision(Position newPos) const;

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
	float stepSpeed;

	std::array<Position, 4> blocks;
	std::chrono::high_resolution_clock::time_point alarm;
};

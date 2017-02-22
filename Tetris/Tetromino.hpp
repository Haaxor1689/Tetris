#pragma once

#include "Enums.hpp"
#include "Event.hpp"
#include "Grid.hpp"
#include "RenderController.hpp"
#include <chrono>

using Timer = std::chrono::high_resolution_clock::time_point;

class Tetromino {
public:
	explicit Tetromino(Grid& grid);

	void input(const Event& event);
	void step();
	void draw(RenderController& renderer);

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
	Timer alarm;
};

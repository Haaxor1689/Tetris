#pragma once

#include "Enums.hpp"
#include "Event.hpp"
#include "Grid.hpp"
#include "RenderController.hpp"
#include <chrono>

using Timer = std::chrono::high_resolution_clock::time_point;

class Tetromino {
public:
	Tetromino(Grid& grid);

	void input(const Event& event);
	void step();
	void draw(RenderController& renderer);

	tetroType getType() const { return type; }
	tetroState getState() const { return state; };
	int getWorth() const { return worth; };

	void setState(tetroState newState) { state = newState; }
	void setStepSpeed(float speed) { stepSpeed = speed; }
	
	void nextType();

	bool resetPosition() noexcept;

	bool nonCollision(Position newPos) const noexcept;

	bool rotate(bool left);
	void setGround() noexcept;
	void drop() { pivot = ground; }

private:
	Grid& grid;
	Position pivot;
	Position ground;
	tetroType type;
	tetroType next;
	tetroState state;
	int worth;
	float stepSpeed;

	std::array<Position, 4> blocks;
	std::array<Position, 4> nextBlocks;
	Timer alarm;
};

#include "Tetromino.hpp"

Tetromino::Tetromino(Grid& grid)
	: grid(grid),
	  pivot({ grid.width / 2, 0 }),
	  state(tetroState::Disabled),
	  worth(100),
	  stepSpeed(0.5f),
	  alarm(std::chrono::high_resolution_clock::now()) {
	nextType();
}

void Tetromino::input(const Event& event) {
	if (event.getType() == eventType::KeyDown) {
		switch (event.getKey()) {
		case SDLK_RIGHT:
			if (nonCollision({ 1, 0 })) {
				pivot.x++;
				setGround();
			}
			break;
		case SDLK_LEFT:
			if (nonCollision({ -1, 0 })) {
				pivot.x--;
				setGround();
			}
			break;
		case SDLK_DOWN:
			if (nonCollision({ 0, 1 }))
				pivot.y++;
			break;
		case SDLK_UP:
		case SDLK_c:
			if (rotate(false))
				setGround();
			break;
		case SDLK_x:
			if (rotate(true))
				setGround();
			break;
		case SDLK_SPACE:
			drop();
			break;
		default:
			break;
		}
	}
}

void Tetromino::step() {
	using namespace std::chrono;

	if (state == tetroState::Falling)
		if (duration_cast<duration<float>>(high_resolution_clock::now() - alarm).count() > stepSpeed) {
			stepSpeed -= stepSpeed / 1000;
			if (nonCollision({ 0, 1 })) {
				worth -= 5;
				pivot.y++;
			} else {
				gridBlock block;
				for (auto& i : blocks) {
					block = toGridBlock(type);
					grid.matrix[pivot.y + i.y][pivot.x + i.x] = block;
				}
				state = tetroState::Disabled;
			}
			alarm = high_resolution_clock::now();
		}
}

void Tetromino::draw(RenderController& renderer) {
	for (const auto& i : blocks) {
		renderer.drawSprite(toString(type), { grid.corner.x + (pivot.x + i.x) * grid.tileSize, grid.corner.y + (pivot.y + i.y) * grid.tileSize });
		renderer.drawSprite(toString(type), { grid.corner.x + (ground.x + i.x) * grid.tileSize, grid.corner.y + (ground.y + i.y) * grid.tileSize }, 100);
	}

	for (const auto& i : nextBlocks)
		renderer.drawSprite(toString(next), { 664 + i.x * grid.tileSize, 46 + i.y * grid.tileSize });
}

void Tetromino::nextType() {
	type = next;
	blocks = toArray(type);
	next = (static_cast<tetroType>(rand() % 7 + 1));
	nextBlocks = toArray(next);
}

bool Tetromino::resetPosition() noexcept {
	pivot = { grid.width / 2, 0 };
	worth = 100;
	setGround();
	return nonCollision({ 0, 0 });
}

bool Tetromino::nonCollision(Position newPos) const noexcept {
	auto empty = true;
	for (const auto& i : blocks)
		if (pivot.x + i.x + newPos.x < 0 ||
			pivot.y + i.y + newPos.y < 0 ||
			pivot.x + i.x + newPos.x >= grid.width ||
			pivot.y + i.y + newPos.y >= grid.height ||
			!grid.isEmpty({ pivot.x + i.x + newPos.x, pivot.y + i.y + newPos.y }))
			empty = false;
	return empty;
}

bool Tetromino::rotate(bool left) {
	if (type == tetroType::O)
		return true;

	auto oldBlocks = blocks;
	for (auto& i : blocks) {
		std::swap(i.x, i.y);
		if (left)
			i.y *= -1;
		else
			i.x *= -1;
	}
	if (!nonCollision({ 0, 0 })) {
		blocks = oldBlocks;
		return false;
	}
	return true;
}

void Tetromino::setGround() noexcept {
	auto i = 0;
	while (nonCollision({ 0, i + 1 })) {
		i++;
	}
	ground.x = pivot.x;
	ground.y = pivot.y + i;
}
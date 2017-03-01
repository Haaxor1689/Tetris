#include "Tetromino.hpp"

Tetromino::Tetromino(Grid& grid)
	: grid(grid),
	  pivot({ grid.width / 2, 0 }),
	  state(tetroState::Disabled),
	  worth(100),
	  stepSpeed(0.5f),
	  alarm(std::chrono::high_resolution_clock::now()) {
	setType();
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
			if (rotateRight())
				setGround();
			break;
		case SDLK_x:
			if (rotateLeft())
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
	auto texture = toString(type);
	switch (state) {
	case tetroState::Falling:
		for (const auto& i : blocks) {
			renderer.drawSprite(texture, { grid.corner.x + (pivot.x + i.x) * grid.tileSize, grid.corner.y + (pivot.y + i.y) * grid.tileSize });
			renderer.drawSprite(texture, { grid.corner.x + (ground.x + i.x) * grid.tileSize, grid.corner.y + (ground.y + i.y) * grid.tileSize }, 100);
		}
		break;
	case tetroState::Waiting:
		for (const auto& i : blocks)
			renderer.drawSprite(texture, { 664 + i.x * grid.tileSize, 46 + i.y * grid.tileSize });
		break;
	case tetroState::Disabled:
		break;
	}
	if (state != tetroState::Disabled) {

	}
}

void Tetromino::setState(tetroState newState) {
	state = newState;
}

tetroState Tetromino::getState() const {
	return state;
}

void Tetromino::setType() {
	srand(static_cast<unsigned>(time(nullptr)));
	setType(static_cast<tetroType>(rand() % 7 + 1));
}

void Tetromino::setType(tetroType newType) {
	type = newType;
	switch (type) {
	case tetroType::I:
		blocks = { { { 0, 0 }, { -1, 0 }, { 1, 0 }, { 2, 0 } } };
		break;
	case tetroType::O:
		blocks = { { { 0, 0 }, { 1, 1 }, { 1, 0 }, { 0, 1 } } };
		break;
	case tetroType::T:
		blocks = { { { 0, 0 }, { -1, 0 }, { 1, 0 }, { 0, 1 } } };
		break;
	case tetroType::J:
		blocks = { { { 0, 0 }, { -1, 0 }, { 1, 0 }, { 1, 1 } } };
		break;
	case tetroType::L:
		blocks = { { { 0, 0 }, { -1, 0 }, { 1, 0 }, { -1, 1 } } };
		break;
	case tetroType::S:
		blocks = { { { 0, 0 }, { -1, 1 }, { 1, 0 }, { 0, 1 } } };
		break;
	case tetroType::Z:
		blocks = { { { 0, 0 }, { -1, 0 }, { 1, 1 }, { 0, 1 } } };
		break;
	case tetroType::None:
		blocks = { { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } } };
	}
}

tetroType Tetromino::getType() const {
	return type;
}

void Tetromino::setStepSpeed(float speed) {
	stepSpeed = speed;
}

int Tetromino::getWorth() const {
	return worth;
}

bool Tetromino::resetPosition() {
	pivot = { grid.width / 2, 0 };
	worth = 100;
	setGround();
	return nonCollision({ 0, 0 });
}

bool Tetromino::nonCollision(Position newPos) const {
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

bool Tetromino::rotateLeft() {
	if (type == tetroType::O)
		return true;

	auto oldBlocks = blocks;
	for (auto& i : blocks) {
		std::swap(i.x, i.y);
		i.y *= -1;
	}
	if (!nonCollision({ 0, 0 })) {
		blocks = oldBlocks;
		return false;
	}
	return true;
}

bool Tetromino::rotateRight() {
	if (type == tetroType::O)
		return true;

	auto oldBlocks = blocks;
	for (auto& i : blocks) {
		std::swap(i.x, i.y);
		i.x *= -1;
	}
	if (!nonCollision({ 0, 0 })) {
		blocks = oldBlocks;
		return false;
	}
	return true;
}

void Tetromino::setGround() {
	auto i = 0;
	while (nonCollision({ 0, i + 1 })) {
		i++;
	}
	ground.x = pivot.x;
	ground.y = pivot.y + i;
}

void Tetromino::drop() {
	pivot = ground;
}

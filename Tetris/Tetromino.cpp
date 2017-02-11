#include "Tetromino.hpp"

Tetromino::Tetromino(Grid& grid)
	: grid(grid),
	pivot({ grid.width / 2, 0 }),
	state(tetroState::Disabled),
	worth(100),
	alarm(std::chrono::high_resolution_clock::now()) {
	setType();
}

void Tetromino::input(const Event& event) {
	if (event.type() == SDL_KEYDOWN) {
		switch (event.key()) {
		case SDLK_RIGHT:
			if (nonCollision({1, 0})) {
				pivot.x++;
				setGround();
			}
			break;
		case SDLK_LEFT:
			if (nonCollision({-1, 0})){
				pivot.x--;
				setGround();
			}
			break;
		case SDLK_DOWN:
			if (nonCollision({0, 1}))
				pivot.y++;
			break;
		case SDLK_UP:
			if (rotateRight())
				setGround();
			break;
		case SDLK_SPACE:
			drop();
			break;
		}
	}
}

void Tetromino::step() {
	using namespace std::chrono;

	if (state == tetroState::Falling)
		if (duration_cast<duration<float> >(high_resolution_clock::now() - alarm).count() > 0.5f) {
			if (nonCollision({0, 1})) {
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

void Tetromino::draw(Renderer& renderer) {
	std::string texture = toString(type);
	switch(state) {
	case tetroState::Falling:
		for (const auto& i : blocks) {
			renderer.drawSprite(texture, { grid.corner.x + (pivot.x + i.x) * grid.tileSize, grid.corner.y + (pivot.y + i.y) * grid.tileSize });
			renderer.drawSprite(texture, { grid.corner.x + (ground.x + i.x) * grid.tileSize, grid.corner.y + (ground.y + i.y) * grid.tileSize }, 100);
		}
		break;
	case tetroState::Waiting:
		for (const auto& i : blocks)
			renderer.drawSprite(texture, { 200 + i.x * grid.tileSize, 200 + i.y * grid.tileSize });
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
	srand(time(NULL));
	setType(static_cast<tetroType>(rand() % 7 + 1));
}

void Tetromino::setType(tetroType newType) {
	type = newType;
	switch(type) {
	case tetroType::I:
		blocks[1] = {-1, 0};
		blocks[2] = {1, 0};
		blocks[3] = {2, 0};
		break;
	case tetroType::O:
		blocks[1] = {1, 0};
		blocks[2] = {0, 1};
		blocks[3] = {1, 1};
		break;
	case tetroType::T:
		blocks[1] = {-1, 0};
		blocks[2] = {1, 0};
		blocks[3] = {0, 1};
		break;
	case tetroType::J:
		blocks[1] = {-1, 0};
		blocks[2] = {1, 0};
		blocks[3] = {1, 1};
		break;
	case tetroType::L:
		blocks[1] = {-1, 0};
		blocks[2] = {1, 0};
		blocks[3] = {-1, 1};
		break;
	case tetroType::S:
		blocks[1] = {-1, 1};
		blocks[2] = {0, 1};
		blocks[3] = {1, 0};
		break;
	case tetroType::Z:
		blocks[1] = {-1, 0};
		blocks[2] = {0, 1};
		blocks[3] = {1, 1};
		break;
	case tetroType::None:
		blocks[1] = {0, 0};
		blocks[2] = {0, 0};
		blocks[3] = {0, 0};
	}
}

tetroType Tetromino::getType() const {
	return type;
}

int Tetromino::getWorth() const {
	return worth;
}

void Tetromino::resetPosition() {
	pivot = {grid.width / 2, 0};
	worth = 100;
	setGround();
}

bool Tetromino::nonCollision(Position newPos) const {
	bool empty = true;
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
	if(!nonCollision({0, 0})) {
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
	if(!nonCollision({0, 0})) {
		blocks = oldBlocks;
		return false;
	}
	return true;
}

void Tetromino::setGround() {
	int i = 0;
	while(nonCollision({0, i + 1})){
		i++;
	}
	ground.x = pivot.x;
	ground.y = pivot.y + i;
}

void Tetromino::drop() {
	pivot = ground;
}
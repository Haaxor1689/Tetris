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
				pivot.y++;
			} else {
				gridBlock block;
				for (auto& i : blocks) {
					switch (type) {
					case tetroType::I:
						block = gridBlock::Teal;
						break;
					case tetroType::O:
						block = gridBlock::Yellow;
						break;
					case tetroType::T:
						block = gridBlock::Purple;
						break;
					case tetroType::J:
						block = gridBlock::Blue;
						break;
					case tetroType::L:
						block = gridBlock::Orange;
						break;
					case tetroType::S:
						block = gridBlock::Green;
						break;
					case tetroType::Z:
						block = gridBlock::Red;
						break;
					case tetroType::None:
						block = gridBlock::Empty;
					}
					grid.matrix[pivot.y + i.y][pivot.x + i.x] = block;
				}
				state = tetroState::Disabled;
			}
			alarm = high_resolution_clock::now();
		}
}

void Tetromino::draw(Renderer& renderer, std::map<std::string, Sprite>& textures) {
	switch(state){
	case tetroState::Falling:
		textures.find(texture)->second.draw(renderer,
		                                    grid.corner.x + (pivot.x + blocks[0].x) * grid.tileSize,
		                                    grid.corner.y + (pivot.y + blocks[0].y) * grid.tileSize);
		textures.find(texture)->second.draw(renderer,
		                                    grid.corner.x + (pivot.x + blocks[1].x) * grid.tileSize,
		                                    grid.corner.y + (pivot.y + blocks[1].y) * grid.tileSize);
		textures.find(texture)->second.draw(renderer,
		                                    grid.corner.x + (pivot.x + blocks[2].x) * grid.tileSize,
		                                    grid.corner.y + (pivot.y + blocks[2].y) * grid.tileSize);
		textures.find(texture)->second.draw(renderer,
		                                    grid.corner.x + (pivot.x + blocks[3].x) * grid.tileSize,
		                                    grid.corner.y + (pivot.y + blocks[3].y) * grid.tileSize);

		textures.find(texture)->second.draw(renderer,
		                                    grid.corner.x + (ground.x + blocks[0].x) * grid.tileSize,
		                                    grid.corner.y + (ground.y + blocks[0].y) * grid.tileSize, 100);
		textures.find(texture)->second.draw(renderer,
		                                    grid.corner.x + (ground.x + blocks[1].x) * grid.tileSize,
		                                    grid.corner.y + (ground.y + blocks[1].y) * grid.tileSize, 100);
		textures.find(texture)->second.draw(renderer,
		                                    grid.corner.x + (ground.x + blocks[2].x) * grid.tileSize,
		                                    grid.corner.y + (ground.y + blocks[2].y) * grid.tileSize, 100);
		textures.find(texture)->second.draw(renderer,
		                                    grid.corner.x + (ground.x + blocks[3].x) * grid.tileSize,
		                                    grid.corner.y + (ground.y + blocks[3].y) * grid.tileSize, 100);
		break;
	case tetroState::Waiting:
		textures.find(texture)->second.draw(renderer,
		                                    200 + blocks[0].x * grid.tileSize,
		                                    200 + blocks[0].y * grid.tileSize);
		textures.find(texture)->second.draw(renderer,
		                                    200 + blocks[1].x * grid.tileSize,
		                                    200 + blocks[1].y * grid.tileSize);
		textures.find(texture)->second.draw(renderer,
		                                    200 + blocks[2].x * grid.tileSize,
		                                    200 + blocks[2].y * grid.tileSize);
		textures.find(texture)->second.draw(renderer,
		                                    200 + blocks[3].x * grid.tileSize,
		                                    200 + blocks[3].y * grid.tileSize);
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
		texture = "TealBlock";
		blocks[1] = {-1, 0};
		blocks[2] = {1, 0};
		blocks[3] = {2, 0};
		break;
	case tetroType::O:
		texture = "YellowBlock";
		blocks[1] = {1, 0};
		blocks[2] = {0, 1};
		blocks[3] = {1, 1};
		break;
	case tetroType::T:
		texture = "PurpleBlock";
		blocks[1] = {-1, 0};
		blocks[2] = {1, 0};
		blocks[3] = {0, 1};
		break;
	case tetroType::J:
		texture = "BlueBlock";
		blocks[1] = {-1, 0};
		blocks[2] = {1, 0};
		blocks[3] = {1, 1};
		break;
	case tetroType::L:
		texture = "OrangeBlock";
		blocks[1] = {-1, 0};
		blocks[2] = {1, 0};
		blocks[3] = {-1, 1};
		break;
	case tetroType::S:
		texture = "GreenBlock";
		blocks[1] = {-1, 1};
		blocks[2] = {0, 1};
		blocks[3] = {1, 0};
		break;
	case tetroType::Z:
		texture = "RedBlock";
		blocks[1] = {-1, 0};
		blocks[2] = {0, 1};
		blocks[3] = {1, 1};
		break;
	case tetroType::None:
		texture = "EmptyBlock";
		blocks[1] = {0, 0};
		blocks[2] = {0, 0};
		blocks[3] = {0, 0};
	}
}

tetroType Tetromino::getType() const {
	return type;
}

void Tetromino::resetPosition() {
	pivot = {grid.width / 2, 0};
	setGround();
}

bool Tetromino::nonCollision(Position newPos) {
	bool empty = true;
	for (const auto& i : blocks)
		if (pivot.x + i.x + newPos.x < 0 ||
		    pivot.y + i.y + newPos.y < 0 ||
		    pivot.x + i.x + newPos.x >= grid.width ||
		    pivot.y + i.y + newPos.y >= grid.height ||
		    grid.matrix[pivot.y + i.y + newPos.y][pivot.x + i.x + newPos.x] != gridBlock::Empty)
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
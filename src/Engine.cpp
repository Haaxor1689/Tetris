#include "Engine.hpp"
#include <sstream>

Engine::Engine()
	: grid({ 360, 12 }, 24),
	  tetromino(grid) {
	// Sprite loading
	renderer.addSprite("Background", "resources/Background.png");
	renderer.addSprite("EmptyBlock", "resources/EmptyBlock.png");
	renderer.addSprite("BlueBlock", "resources/BlueBlock.png");
	renderer.addSprite("GreenBlock", "resources/GreenBlock.png");
	renderer.addSprite("OrangeBlock", "resources/OrangeBlock.png");
	renderer.addSprite("PurpleBlock", "resources/PurpleBlock.png");
	renderer.addSprite("RedBlock", "resources/RedBlock.png");
	renderer.addSprite("TealBlock", "resources/TealBlock.png");
	renderer.addSprite("YellowBlock", "resources/YellowBlock.png");

	// Font loading
	renderer.addFont("Title", "resources/Bitmgothic.ttf", 60);
	renderer.addFont("MenuItem", "resources/8BitSnobbery.ttf", 24);
	renderer.addFont("Text", "resources/8BitSnobbery.ttf", 12);

	// Buttons setup
	buttons.insert(std::make_pair("New Game", Button({ 480, 300 }, 100, 30, "New Game (N)", "MenuItem", "_None", { std::bind(&Engine::bNewGame, this) }, SDLK_n)));
	buttons.insert(std::make_pair("Continue", Button({ 480, 340 }, 100, 30, "Continue (C)", "MenuItem", "_None", [&]() { state = gameState::play; }, SDLK_c)));
	buttons.insert(std::make_pair("Quit", Button({ 480, 380 }, 100, 30, "Quit (Q)", "MenuItem", "_None", [&]() { state = gameState::exit; }, SDLK_q)));
}

void Engine::run() {
	srand(static_cast<unsigned>(time(nullptr)));
	while (state != gameState::exit) {
		Event event;
		while (event.poll())
			input(event);

		step();
		draw();
	}
}

void Engine::input(const Event& event) {
	if (event.getType() == eventType::Quit) {
		state = gameState::exit;
	}

	switch (state) {
		case gameState::intro:
			if (event.getType() == eventType::KeyDown || event.getType() == eventType::MouseButtonUp)
				state = gameState::menu;
			break;
		case gameState::menu:
			for (auto& i : buttons)
				i.second.input(event);
		case gameState::play:
			tetromino.input(event);

			if (event.getType() == eventType::KeyDown) {
				switch (event.getKey()) {
					case SDLK_ESCAPE:
						state = gameState::menu;
						break;
					default:
						break;
				}
			}
			break;
		case gameState::gameover:
			if (event.getType() == eventType::KeyDown) {
				switch (event.getKey()) {
					case SDLK_ESCAPE:
						state = gameState::menu;
						score = 0;
						tetromino.setStepSpeed(0.5f);
						break;
					default:
						break;
				}
			}
		default:
			break;
	}
}

void Engine::step() {
	bool rowDone;
	switch (state) {
		case gameState::play:
			tetromino.step();

			if (tetromino.getState() == tetroState::Disabled) {
				multiplier = 1;
				for (int j = grid.matrix.size() - 1; j >= 0; --j) {
					rowDone = true;
					for (auto& i : grid.matrix[j])
						if (i == gridBlock::Empty)
							rowDone = false;

					if (rowDone) {
						lastScored += 100 * static_cast<int>(0.5 + multiplier);
						grid.done.push_front(grid.matrix[j]);
						grid.matrix[j].fill(gridBlock::Empty);
						for (auto i = j; i > 0; --i)
							swap(grid.matrix[i], grid.matrix[i - 1]);
						++multiplier;
						++j;
					}
				}
				lastScored += tetromino.getWorth();

				tetromino.setState(tetroState::Falling);
				tetromino.nextType();
				if (!tetromino.resetPosition()) {
					state = gameState::gameover;
					score += lastScored;
					lastScored = 0;
				}
			}
			break;
		default:
			break;
	}
}

void Engine::draw() {
	SDL_RenderClear(renderer.getRenderer());

	std::ostringstream oss;
	renderer.drawSprite("Background", { 0, 0 });
	switch (state) {
		case gameState::intro:
			renderer.drawText("Tetris", "Title", { 480, 120 });
			renderer.drawText("Press any key to start", "MenuItem", { 480, 450 });
			break;
		case gameState::menu:
			for (auto& i : buttons)
				i.second.draw(renderer);
			renderer.drawText("Tetris", "Title", { 480, 120 });
			renderer.drawText("Controlls:", "MenuItem", { 140, 390 }, horizontalAlign::Left);
			renderer.drawText("Movement - Arrows", "Text", { 140, 415 }, horizontalAlign::Left);
			renderer.drawText("Drop - Space", "Text", { 140, 430 }, horizontalAlign::Left);
			renderer.drawText("Rotate - X/C", "Text", { 140, 445 }, horizontalAlign::Left);
			renderer.drawText("Pause - Esc", "Text", { 140, 460 }, horizontalAlign::Left);
			break;
		case gameState::play:
			oss << "Score: " << score;
			renderer.drawText(oss.str(), "MenuItem", { 140, 20 }, horizontalAlign::Left, verticalAlign::Top);
			renderer.drawText("Next:", "MenuItem", { 640, 20 }, horizontalAlign::Left, verticalAlign::Top);

			if (lastScored != 0) {
				oss.str(std::string());
				oss << "+ " << lastScored;
				renderer.drawText(oss.str(), "MenuItem", { 185, 44 }, horizontalAlign::Left, verticalAlign::Top);
				++score;
				--lastScored;
			}

			for (unsigned j = 0; j < grid.matrix.size(); ++j)
				for (unsigned i = 0; i < grid.matrix[j].size(); ++i)
					renderer.drawSprite(toString(grid.matrix[j][i]), { grid.corner.x + static_cast<int>(i) * grid.tileSize, grid.corner.y + static_cast<int>(j) * grid.tileSize });

			for (unsigned j = 0; j < grid.done.size(); ++j)
				for (unsigned i = 0; i < grid.done[j].size(); ++i)
					renderer.drawSprite(toString(grid.done[j][i]), { grid.corner.x + 264 + static_cast<int>(i) * grid.tileSize, grid.corner.y + 480 - static_cast<int>(grid.done.size()) * grid.tileSize + static_cast<int>(j) * grid.tileSize });

			tetromino.draw(renderer);
			break;
		case gameState::gameover:
			renderer.drawText("Game Over", "Title", { 480, 120 });
			oss << "Final score: " << score << " points";
			renderer.drawText(oss.str(), "MenuItem", { 480, 200 });
			renderer.drawText("Press Escape to continue", "MenuItem", { 480, 450 });
			break;
		default:
			break;
	}

	SDL_RenderPresent(renderer.getRenderer());
}

void Engine::bNewGame() {
	state = gameState::play;
	score = 0;
	lastScored = 0;
	grid.reset();
	tetromino.nextType();
	tetromino.resetPosition();
	tetromino.setGround();
	tetromino.setStepSpeed(0.5f);
}
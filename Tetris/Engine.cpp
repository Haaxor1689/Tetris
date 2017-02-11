#include "Engine.hpp"

Engine::Engine() : state(gameState::intro), grid({360, 12}, 24), score(0), lastScored(0), tetroFalling(grid), tetroWaiting(grid), alarm(std::chrono::high_resolution_clock::now()) {
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
	renderer.addFont("MenuItem", "resources/Bitmgothic.ttf", 20);

	// Randomize waiting tetormino
	tetroWaiting.setType();
}

void Engine::run() {
	tetroFalling.setState(tetroState::Falling);
	tetroWaiting.setState(tetroState::Waiting);

	while(state != gameState::exit) {
		//	Input handling
		while (SDL_PollEvent(&event.get()))
			input(event);

		// Game logic
		step();

		// Game drawing
		draw();
	}
}

void Engine::input(const Event& event) {
	if (event.type() == SDL_QUIT) {
		state = gameState::exit;
	}

	switch(state){
	case gameState::intro:
		if (event.type() == SDL_KEYDOWN) {
			state = gameState::menu;
		}
		break;
	case gameState::menu:
		if (event.type() == SDL_KEYDOWN) {
			switch(event.key()) {
			case SDLK_n:
				state = gameState::play;
				tetroFalling.setType();
				grid.reset();
				tetroFalling.resetPosition();
				tetroFalling.setGround();
				tetroWaiting.setType();
				break;
			case SDLK_c:
				state = gameState::play;
				break;
			case SDLK_ESCAPE:
				state = gameState::exit;
				break;
			}
		}
		break;
	case gameState::play:
		tetroFalling.input(event);

		if (event.type() == SDL_KEYDOWN) {
			switch (event.key()) {
			case SDLK_ESCAPE:
				state = gameState::menu;
				score = 0;
				break;
			}
		}
		break;
	case gameState::gameover:
		if (event.type() == SDL_KEYDOWN) {
			state = gameState::menu;
			score = 0;
		}
	default:
		break;
	}
}

void Engine::step() {
	bool rowDone;
	switch(state) {
	case gameState::play:
		tetroFalling.step();
		tetroWaiting.step();

		if (tetroFalling.getState() == tetroState::Disabled) {
			lastScored = 0;
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
					for (int i = j; i > 0; --i)
						std::swap(grid.matrix[i], grid.matrix[i - 1]);
					++multiplier;
					++j;
				}
			}
			lastScored += tetroFalling.getWorth();
			score += lastScored;


			tetroFalling.setState(tetroState::Falling);
			tetroFalling.setType(tetroWaiting.getType());
			tetroFalling.resetPosition();
			tetroWaiting.setType();
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
	switch(state) {
	case gameState::intro:
		renderer.drawText("Tetris", "Title", { 480, 120 });
		renderer.drawText("Press any key to start", "MenuItem", { 480, 500 });
		break;
	case gameState::menu:
		renderer.drawText("Tetris", "Title", { 480, 120 });
		renderer.drawText("New Game (N)", "MenuItem", { 480, 300 });
		renderer.drawText("Continue (C)", "MenuItem", { 480, 340 });
		renderer.drawText("Quit (Esc)", "MenuItem", { 480, 380 });
		break;
	case gameState::play:
		oss << "Score: " << score << " points";
		renderer.drawText(oss.str(), "MenuItem", { 140, 20 }, { 255, 255, 255, 255 }, textHAlign::left, textVAlign::top);

		oss.str(std::string());
		oss << "Last Scored: " << lastScored << " points";
		renderer.drawText(oss.str(), "MenuItem", { 140, 60 }, { 255, 255, 255, 255 }, textHAlign::left, textVAlign::top);

		for (int j = 0; j < grid.matrix.size(); ++j)
			for (int i = 0; i < grid.matrix[j].size(); ++i)
				renderer.drawSprite(toString(grid.matrix[j][i]), { grid.corner.x + i * grid.tileSize, grid.corner.y + j * grid.tileSize });

		for (int j = 0; j < grid.done.size(); ++j)
			for (int i = 0; i < grid.done[j].size(); ++i)
				renderer.drawSprite(toString(grid.done[j][i]), { grid.corner.x + 264 + i * grid.tileSize, grid.corner.y + j * grid.tileSize });

		tetroFalling.draw(renderer);
		tetroWaiting.draw(renderer);
		break;

	default:
		renderer.drawText("Placeholder", "Title", { 480, 300 });
		break;
	}

	SDL_RenderPresent(renderer.getRenderer());
}
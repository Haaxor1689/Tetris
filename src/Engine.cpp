#include "Engine.hpp"
#include <sstream>

Engine::Engine() : state(gameState::intro),
						 score(0),
						 lastScored(0),
						 multiplier(0),
						 grid({ 360, 12 }, 24),
						 tetroFalling(grid),
						 tetroWaiting(grid),
						 alarm(std::chrono::high_resolution_clock::now()) {
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
	renderer.addFont("Text", "resources/Bitmgothic.ttf", 14);

	// Randomize waiting tetormino
	tetroWaiting.setType();
}

void Engine::run() {
	tetroFalling.setState(tetroState::Falling);
	tetroWaiting.setState(tetroState::Waiting);

	while (state != gameState::exit) {
		//	Input handling
		while (SDL_PollEvent(&event))
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

	switch (state) {
	case gameState::intro:
		if (event.type() == SDL_KEYDOWN) {
			state = gameState::menu;
		} else if (event.type() == SDL_MOUSEBUTTONUP)
			state = gameState::menu;
		break;
	case gameState::menu:
		if (event.type() == SDL_KEYDOWN) {
			switch (event.key()) {
			case SDLK_n:
				state = gameState::play;
				score = 0;
				lastScored = 0;
				grid.reset();
				tetroFalling.setType();
				tetroFalling.resetPosition();
				tetroFalling.setGround();
				tetroWaiting.setType();
				tetroFalling.setStepSpeed(0.5f);
				break;
			case SDLK_c:
				state = gameState::play;
				break;
			case SDLK_ESCAPE:
				state = gameState::exit;
				break;
			default:
				break;
			}
		} else if (event.type() == SDL_MOUSEBUTTONUP) {
			if (event.position().x > 400 && 
				 event.position().x < 560 && 
				 event.position().y > 340 &&
				 event.position().y < 420)
				state = gameState::exit;
		}
		break;
	case gameState::play:
		tetroFalling.input(event);

		if (event.type() == SDL_KEYDOWN) {
			switch (event.key()) {
			case SDLK_ESCAPE:
				state = gameState::menu;
				break;
			default:
				break;
			}
		}
		break;
	case gameState::gameover:
		if (event.type() == SDL_KEYDOWN) {
			switch (event.key()) {
			case SDLK_ESCAPE:
				state = gameState::menu;
				score = 0;
				tetroFalling.setStepSpeed(0.5f);
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
		tetroFalling.step();
		tetroWaiting.step();

		if (tetroFalling.getState() == tetroState::Disabled) {
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
			lastScored += tetroFalling.getWorth();

			tetroFalling.setState(tetroState::Falling);
			tetroFalling.setType(tetroWaiting.getType());
			tetroWaiting.setType();
			if (!tetroFalling.resetPosition()) {
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
		renderer.drawText("Tetris", "Title", { 480, 120 });
		renderer.drawText("New Game (N)", "MenuItem", { 480, 300 });
		renderer.drawText("Continue (C)", "MenuItem", { 480, 340 });
		renderer.drawText("Quit (Esc)", "MenuItem", { 480, 380 });
		renderer.drawText("Controlls:", "MenuItem", { 140, 390 }, { 255, 255, 255, 255 }, textHAlign::left);
		renderer.drawText("Movement - Arrows", "Text", { 140, 415 }, { 255, 255, 255, 255 }, textHAlign::left);
		renderer.drawText("Drop - Space", "Text", { 140, 430 }, { 255, 255, 255, 255 }, textHAlign::left);
		renderer.drawText("Rotate - X/C", "Text", { 140, 445 }, { 255, 255, 255, 255 }, textHAlign::left);
		renderer.drawText("Pause - Esc", "Text", { 140, 460 }, { 255, 255, 255, 255 }, textHAlign::left);
		break;
	case gameState::play:
		oss << "Score: " << score;
		renderer.drawText(oss.str(), "MenuItem", { 140, 20 }, { 255, 255, 255, 255 }, textHAlign::left, textVAlign::top);
		renderer.drawText("Next:", "MenuItem", { 640, 20 }, { 255, 255, 255, 255 }, textHAlign::left, textVAlign::top);

		if (lastScored != 0) {
			oss.str(std::string());
			oss << "+ " << lastScored;
			renderer.drawText(oss.str(), "MenuItem", { 185, 44 }, { 255, 255, 255, 255 }, textHAlign::left, textVAlign::top);
			++score;
			--lastScored;
		}

		for (unsigned j = 0; j < grid.matrix.size(); ++j)
			for (unsigned i = 0; i < grid.matrix[j].size(); ++i)
				renderer.drawSprite(toString(grid.matrix[j][i]), { grid.corner.x + static_cast<int>(i) * grid.tileSize, grid.corner.y + static_cast<int>(j) * grid.tileSize });

		/*
		for (unsigned j = 0; j < grid.done.size(); ++j)
			for (unsigned i = 0; i < grid.done[j].size(); ++i)
				renderer.drawSprite(toString(grid.done[j][i]), { grid.corner.x + 264 + static_cast<int>(i) * grid.tileSize, grid.corner.y + 480 - static_cast<int>(grid.done.size()) * grid.tileSize + static_cast<int>(j) * grid.tileSize });
				*/ 

		tetroFalling.draw(renderer);
		tetroWaiting.draw(renderer);
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

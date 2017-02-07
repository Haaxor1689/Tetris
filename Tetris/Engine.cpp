#include "Engine.hpp"
Engine::Engine() :
		state(gameState::intro),
		grid({360, 12}, 24),
		score(0),
		tetroFalling(grid),
		tetroWaiting(grid),
		alarm(std::chrono::high_resolution_clock::now()) {
	// Sprite loading
	textures.insert(std::make_pair("Background", Sprite("resources/Background.png", renderer)));
	textures.insert(std::make_pair("EmptyBlock", Sprite("resources/EmptyBlock.png", renderer)));
	textures.insert(std::make_pair("BlueBlock", Sprite("resources/BlueBlock.png", renderer)));
	textures.insert(std::make_pair("GreenBlock", Sprite("resources/GreenBlock.png", renderer)));
	textures.insert(std::make_pair("OrangeBlock", Sprite("resources/OrangeBlock.png", renderer)));
	textures.insert(std::make_pair("PurpleBlock", Sprite("resources/PurpleBlock.png", renderer)));
	textures.insert(std::make_pair("RedBlock", Sprite("resources/RedBlock.png", renderer)));
	textures.insert(std::make_pair("TealBlock", Sprite("resources/TealBlock.png", renderer)));
	textures.insert(std::make_pair("YellowBlock", Sprite("resources/YellowBlock.png", renderer)));

	// Font loading
	fonts.insert(std::make_pair("Title", Font("resources/Bitmgothic.ttf", 60)));
	fonts.insert(std::make_pair("MenuItem", Font("resources/Bitmgothic.ttf", 20)));

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

		multiplier = 1;
		for (int j = 0; j < grid.matrix.size(); ++j) {
			rowDone = true;
			for (auto& i : grid.matrix[j])
				if (i == gridBlock::Empty)
					rowDone = false;
			if (rowDone) {
				score +=  100 * (1.5 * multiplier);
				grid.matrix[j].fill(gridBlock::Empty);
				for (int i = j; i > 0; --i)
					std::swap(grid.matrix[i], grid.matrix[i - 1]);
			}
		}

		if (tetroFalling.getState() == tetroState::Disabled) {
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
	SDL_RenderClear(renderer.renderer);

	std::ostringstream oss;
	sprite("Background", 0, 0);
	switch(state) {
	case gameState::intro:
		text("Tetris", "Title", 480, 120);
		text("Press any key to start", "MenuItem", 480, 500);
		break;
	case gameState::menu:
		text("Tetris", "Title", 480, 120);
		text("New Game (N)", "MenuItem", 480, 300);
		text("Continue (C)", "MenuItem", 480, 340);
		text("Quit (Esc)", "MenuItem", 480, 380);
		break;
	case gameState::play:
		oss << "Score: " << score << " points";
		text(oss.str(), "MenuItem", 140, 20, { 255, 255, 255, 255 }, textHAlign::left, textVAlign::top);

		for (int j = 0; j < grid.matrix.size(); ++j)
			for (int i = 0; i < grid.matrix[j].size(); ++i) {
				std::string texture;
				switch(grid.matrix[j][i]) {
				case gridBlock::Empty:
					texture = "EmptyBlock";
					break;
				case gridBlock::Blue:
					texture = "BlueBlock";
					break;
				case gridBlock::Green:
					texture = "GreenBlock";
					break;
				case gridBlock::Orange:
					texture = "OrangeBlock";
					break;
				case gridBlock::Purple:
					texture = "PurpleBlock";
					break;
				case gridBlock::Red:
					texture = "RedBlock";
					break;
				case gridBlock::Teal:
					texture = "TealBlock";
					break;
				case gridBlock::Yellow:
					texture = "YellowBlock";
					break;
				}
				sprite(texture, grid.corner.x + i * grid.tileSize, grid.corner.y + j * grid.tileSize);
			}


		tetroFalling.draw(renderer, textures);
		tetroWaiting.draw(renderer, textures);
		break;
	default:
		text("Placeholder", "Title", 480, 300);
		break;
	}

	SDL_RenderPresent(renderer.renderer);
}

Engine::~Engine() {
}

void Engine::text(std::string text, std::string font, int x, int y, SDL_Color color, textHAlign hAlign, textVAlign vAlign) {
	fonts.find(font)->second.draw(renderer, text, x, y, hAlign, vAlign, color);
}

void Engine::sprite(std::string texture, int x, int y) {
	textures.find(texture)->second.draw(renderer, x, y);
}

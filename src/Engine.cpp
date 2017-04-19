#include "Engine.hpp"
#include <sstream>
#include "MinMaxClamp.hpp"

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

	// Buttons set up
	addButton("New Game (N)", { 480, 300 }, 180, 30, &Engine::bNewGame, SDLK_n, "MenuItem", "YellowBlock");
	addButton("Continue (C)", { 480, 340 }, 160, 30, &Engine::bContinue, SDLK_c, "MenuItem", "YellowBlock");
	addButton("Quit (Q)", { 480, 380 }, 110, 30, &Engine::bQuit, SDLK_q, "MenuItem", "YellowBlock");
}

void Engine::run() {
	while (state != gameState::exit) {
		switch (state) {
		case gameState::exit: loop<gameState::exit>(); break;
		case gameState::intro: loop<gameState::intro>(); break;
		case gameState::menu: loop<gameState::menu>(); break;
		case gameState::play: loop<gameState::play>(); break;
		case gameState::gameover: loop<gameState::gameover>(); break;
		}
	}
}

template<>
void Engine::input<gameState::intro>(const Event& event) {
	if (event.getType() == eventType::Quit)
		state = gameState::exit;

	if (event.getType() == eventType::KeyDown || event.getType() == eventType::MouseButtonUp)
		state = gameState::menu;
}

template<>
void Engine::input<gameState::menu>(const Event& event) {
	if (event.getType() == eventType::Quit)
		state = gameState::exit;
	
	for (auto& i : buttons)
		i.second.input(event);
}

template<>
void Engine::input<gameState::play>(const Event& event) {
	if (event.getType() == eventType::Quit)
		state = gameState::exit;
	
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
}

template<>
void Engine::input<gameState::gameover>(const Event& event) {
	if (event.getType() == eventType::Quit)
		state = gameState::exit;
	
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
}

template<>
void Engine::step<gameState::play>() {
	bool rowDone;
	tetromino.step();

	// TODO - score counter
	score += max(lastScored << 4, 1u);
	lastScored -= max(lastScored << 4, 1u);

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
}

template<>
void Engine::draw<gameState::intro>() {
	SDL_RenderClear(renderer.getRenderer());
	renderer.drawSprite("Background", { 0, 0 });
	renderer.drawText("Tetris", "Title", { 480, 120 });
	renderer.drawText("Press any key to start", "MenuItem", { 480, 450 });
	SDL_RenderPresent(renderer.getRenderer());
}

template<>
void Engine::draw<gameState::menu>() {
	SDL_RenderClear(renderer.getRenderer());
	renderer.drawSprite("Background", { 0, 0 });
	for (auto& i : buttons)
		i.second.draw(renderer);
	renderer.drawText("Tetris", "Title", { 480, 120 });
	renderer.drawText("Controlls:", "MenuItem", { 140, 390 }, horizontalAlign::Left);
	renderer.drawText("Movement - Arrows", "Text", { 140, 415 }, horizontalAlign::Left);
	renderer.drawText("Drop - Space", "Text", { 140, 430 }, horizontalAlign::Left);
	renderer.drawText("Rotate - X/C", "Text", { 140, 445 }, horizontalAlign::Left);
	renderer.drawText("Pause - Esc", "Text", { 140, 460 }, horizontalAlign::Left);
	SDL_RenderPresent(renderer.getRenderer());
}

template<>
void Engine::draw<gameState::play>() {
	SDL_RenderClear(renderer.getRenderer());
	renderer.drawSprite("Background", { 0, 0 });
	std::ostringstream oss;
	oss << "Score: " << score;
	renderer.drawText(oss.str(), "MenuItem", { 140, 20 }, horizontalAlign::Left, verticalAlign::Top);
	renderer.drawText("Next:", "MenuItem", { 640, 20 }, horizontalAlign::Left, verticalAlign::Top);

	if (lastScored != 0) {
		oss.str(std::string());
		oss << "+ " << lastScored;
		renderer.drawText(oss.str(), "MenuItem", { 185, 44 }, horizontalAlign::Left, verticalAlign::Top);
	}

	for (unsigned j = 0; j < grid.matrix.size(); ++j)
		for (unsigned i = 0; i < grid.matrix[j].size(); ++i)
			renderer.drawSprite(toString(grid.matrix[j][i]), { grid.corner.x + static_cast<int>(i) * grid.tileSize, grid.corner.y + static_cast<int>(j) * grid.tileSize });

	for (unsigned j = 0; j < grid.done.size(); ++j)
		for (unsigned i = 0; i < grid.done[j].size(); ++i)
			renderer.drawSprite(toString(grid.done[j][i]), { grid.corner.x + 264 + static_cast<int>(i) * grid.tileSize, grid.corner.y + 480 - static_cast<int>(grid.done.size()) * grid.tileSize + static_cast<int>(j) * grid.tileSize });

	tetromino.draw(renderer);
	SDL_RenderPresent(renderer.getRenderer());
}

template<>
void Engine::draw<gameState::gameover>() {
	SDL_RenderClear(renderer.getRenderer());
	renderer.drawSprite("Background", { 0, 0 });
	std::ostringstream oss;
	renderer.drawText("Game Over", "Title", { 480, 120 });
	oss << "Final score: " << score << " points";
	renderer.drawText(oss.str(), "MenuItem", { 480, 200 });
	renderer.drawText("Press Escape to continue", "MenuItem", { 480, 450 });
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

void Engine::bContinue() {
	state = gameState::play;
}

void Engine::bQuit() {
	state = gameState::exit;
}

void Engine::addButton(std::string name,
                       Position pos,
                       unsigned width,
                       unsigned height,
                       void (Engine::* function)(),
                       int shortcut,
                       const std::string& font,
                       const std::string& sprite) {
	buttons.insert(std::make_pair(name, Button(name, pos, width, height, { std::bind(function, this) }, shortcut, font, sprite)));
}
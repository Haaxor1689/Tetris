#include "Engine.hpp"
#include <fstream>

int main(int, char* []) {
	try {
		// SDL Initialization
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
			throw std::runtime_error(SDL_GetError());

		// IMG Initialization
		if (IMG_Init(IMG_INIT_PNG) == 0)
			throw std::runtime_error(SDL_GetError());

		// TTF Initialization
		if (TTF_Init() != 0)
			throw std::runtime_error(SDL_GetError());

		Engine engine;
		engine.run();
	} catch (const std::exception& Err) {
		std::ofstream errorLog;
		errorLog.open("errorLog.txt");
		errorLog << "Error: " << Err.what() << std::endl;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return -1;
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}

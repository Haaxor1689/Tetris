#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

template <typename Type>
class Wrapper {
public:
	Wrapper() : ptr(nullptr) {}

	Wrapper(Type* window) : ptr(window) {
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
	}

	Wrapper& operator=(Type* window) {
		ptr = window;
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
		return *this;
	}

	Wrapper(const Wrapper& other) = delete;
	Wrapper& operator=(const Wrapper&) = delete;

	Wrapper(Wrapper&& other) noexcept { ptr = std::move(other.ptr); }

	Wrapper& operator=(Wrapper&& other) noexcept {
		ptr = std::move(other.ptr);
		return *this;
	}

	Type* operator&() const { return ptr; }

	~Wrapper() { free(ptr); }

private:
	Type* ptr;
};

inline void free(SDL_Window* ptr) {
	if (!ptr)
		SDL_DestroyWindow(ptr);
}

inline void free(SDL_Renderer* ptr) {
	if (!ptr)
		SDL_DestroyRenderer(ptr);
}

inline void free(SDL_Surface* ptr) {
	if (!ptr)
		SDL_FreeSurface(ptr);
}

inline void free(SDL_Texture* ptr) {
	if (!ptr)
		SDL_DestroyTexture(ptr);
}

inline void free(TTF_Font* ptr) {
	if (!ptr)
		TTF_CloseFont(ptr);
}

using Window = Wrapper<SDL_Window>;
using Renderer = Wrapper<SDL_Renderer>;
using Surface = Wrapper<SDL_Surface>;
using Texture = Wrapper<SDL_Texture>;
using Font = Wrapper<TTF_Font>;

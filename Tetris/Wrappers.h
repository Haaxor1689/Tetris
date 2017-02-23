#pragma once

#include <SDL.h>


struct Window {
	Window() : ptr(nullptr) {}

	Window(SDL_Window* window) : ptr(window) {
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
	}

	Window& operator=(SDL_Window* window) {
		ptr = window;
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
		return *this;
	}

	Window(const Window& other) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&& other) = delete;
	Window& operator=(Window&& other) = delete;

	SDL_Window* operator&() const {
		return ptr;
	}

	~Window() {
		if (!ptr)
			SDL_DestroyWindow(ptr);
	}

private:
	SDL_Window* ptr;
};

struct Renderer {
	Renderer() : ptr(nullptr) {}

	Renderer(SDL_Renderer* renderer) : ptr(renderer) {
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
	}

	Renderer& operator=(SDL_Renderer* renderer) {
		ptr = renderer;
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
		return *this;
	}

	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;
	Renderer(Renderer&& other) = delete;
	Renderer& operator=(Renderer&& other) = delete;

	SDL_Renderer* operator&() const {
		return ptr;
	}

	~Renderer() {
		if (!ptr)
			SDL_DestroyRenderer(ptr);
	}

private:
	SDL_Renderer* ptr;
};

struct Surface {
	Surface() : ptr(nullptr) {}

	Surface(SDL_Surface* surface) : ptr(surface) {
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
	}
	Surface& operator=(SDL_Surface* surface) {
		ptr = surface;
		if (!ptr)
			throw std::runtime_error(SDL_GetError());

		return *this;
	}

	SDL_Surface* operator&() const {
		return ptr;
	}

	~Surface() {
		if(!ptr)
			SDL_FreeSurface(ptr);
	}

private:
	SDL_Surface* ptr;
};

struct Texture {
	Texture() : ptr(nullptr) {}

	Texture(SDL_Texture* texture) : ptr(texture) {
		if (!ptr)
			throw std::runtime_error(SDL_GetError());
	}
	Texture& operator=(SDL_Texture* texture) {
		ptr = texture;
		if (!ptr)
			throw std::runtime_error(SDL_GetError());

		return *this;
	}

	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	Texture(Texture&& other) = default;
	Texture& operator=(Texture&& other) = default;

	SDL_Texture* operator&() const {
		return ptr;
	}

	~Texture() {
		if(!ptr)
			SDL_DestroyTexture(ptr);
	}
	
private:
	SDL_Texture* ptr;
};
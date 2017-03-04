#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class _WrapperAccesor {
	template <typename Type>
	class Wrapper {
	public:
		// Assert restricting Wrapper template to be specialized only for SDL resource classes
		static_assert(std::is_same<Type, SDL_Window>::value |
						  std::is_same<Type, SDL_Renderer>::value |
						  std::is_same<Type, SDL_Surface>::value |
						  std::is_same<Type, SDL_Texture>::value |
						  std::is_same<Type, TTF_Font>::value,
						  "Given type isn't SDL resource type.");
		Wrapper() = default;

		Wrapper(Type* resource) {
			free(ptr);
			ptr = resource;
			if (!ptr)
				throw std::runtime_error(SDL_GetError());
		}

		Wrapper& operator=(Type* resource) {
			free(ptr);
			ptr = resource;
			if (!ptr)
				throw std::runtime_error(SDL_GetError());
			return *this;
		}

		Wrapper(const Wrapper& other) = delete;
		Wrapper& operator=(const Wrapper&) = delete;

		Wrapper(Wrapper&& other) noexcept {
			free(ptr);
			ptr = std::move(other.ptr);
		}

		Wrapper& operator=(Wrapper&& other) noexcept {
			free(ptr);
			ptr = std::move(other.ptr);
			return *this;
		}

		Type* operator&() const { return ptr; }

		~Wrapper() { free(ptr); }

		void free(SDL_Window* ptr) {
			if (!ptr)
				SDL_DestroyWindow(ptr);
		}

		void free(SDL_Renderer* ptr) {
			if (!ptr)
				SDL_DestroyRenderer(ptr);
		}

		void free(SDL_Surface* ptr) {
			if (!ptr)
				SDL_FreeSurface(ptr);
		}

		void free(SDL_Texture* ptr) {
			if (!ptr)
				SDL_DestroyTexture(ptr);
		}

		void free(TTF_Font* ptr) {
			if (!ptr)
				TTF_CloseFont(ptr);
		}

	private:
		Type* ptr = nullptr;
	};

public:
	// Type aliases to be used instead of templated class name
	using WindowAccessor = Wrapper<SDL_Window>;
	using RendererAccessor = Wrapper<SDL_Renderer>;
	using SurfaceAccessor = Wrapper<SDL_Surface>;
	using TextureAccessor = Wrapper<SDL_Texture>;
	using FontAccessor = Wrapper<TTF_Font>;
};

using Window = _WrapperAccesor::WindowAccessor;
using Renderer = _WrapperAccesor::RendererAccessor;
using Surface = _WrapperAccesor::SurfaceAccessor;
using Texture = _WrapperAccesor::TextureAccessor;
using Font = _WrapperAccesor::FontAccessor;
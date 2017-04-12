#pragma once

#include <SDL.h>
#include <SDL_FontCache.h>

class _WrapperAccesor {
	template <typename Type>
	class Wrapper {
	public:
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

	private:
		static void free(SDL_Window* ptr) { if (!ptr) SDL_DestroyWindow(ptr); }
		static void free(SDL_Renderer* ptr) { if (!ptr) SDL_DestroyRenderer(ptr); }
		static void free(SDL_Surface* ptr) { if (!ptr) SDL_FreeSurface(ptr); }
		static void free(SDL_Texture* ptr) { if (!ptr) SDL_DestroyTexture(ptr); }
		static void free(FC_Font* ptr) { if (!ptr) FC_FreeFont(ptr); }

		Type* ptr = nullptr;
	};

	

public:
	// Type aliases to be used instead of templated class name
	using WindowAccessor = Wrapper<SDL_Window>;
	using RendererAccessor = Wrapper<SDL_Renderer>;
	using SurfaceAccessor = Wrapper<SDL_Surface>;
	using TextureAccessor = Wrapper<SDL_Texture>;
	using FontAccessor = Wrapper<FC_Font>;
};

using Window = _WrapperAccesor::WindowAccessor;
using Renderer = _WrapperAccesor::RendererAccessor;
using Surface = _WrapperAccesor::SurfaceAccessor;
using Texture = _WrapperAccesor::TextureAccessor;
using Font = _WrapperAccesor::FontAccessor;
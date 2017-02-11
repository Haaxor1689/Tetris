#pragma once

#include <chrono>
#include <map>
#include <vector>
#include "Position.hpp"
#include "Renderer.hpp"


/* NOT IMPLEMENTED */

struct Particle {
	Particle(int x, int y) : alive(true),
									 pivot({ x, y }),
									 speed(1.0f),
									 alpha(255),
									 alarm(std::chrono::high_resolution_clock::now()) {
	}

	void step() {
		if (alpha <= 0) {
			alive = false;
			return;
		}

		using namespace std::chrono;
		if (duration_cast<duration<float>>(high_resolution_clock::now() - alarm).count() > speed) {
			pivot.x--;
			alpha -= 25;
			alarm = high_resolution_clock::now();
		}
	}

	bool alive;
	Position pivot;
	float speed;
	int alpha;
	std::chrono::high_resolution_clock::time_point alarm;
};

class ParticleEmitter {
public:
	ParticleEmitter(int x, int y, std::string texture) : active(false),
																		  pivot({ x, y }),
																		  texture(texture) {
	}

	void activate() {
		active = true;
	}

	void deactivate() {
		active = false;
	}

	void step() {
		if (active)
			for (auto& i : particles) {
				if (i.alive)
					i.step();
			}
	}

	void draw(Renderer& renderer, std::map<std::string, Sprite>& textures) {
		for (const auto& i : particles) {
			if (i.alive)
				renderer.drawSprite(texture, { i.pivot.x, i.pivot.y }, i.alpha);
		}
	}

private:
	bool active;
	Position pivot;
	std::string texture;
	std::vector<Particle> particles;
};

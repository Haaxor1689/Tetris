#ifndef TETRIS_PARTICLEEMITTER_HPP
#define TETRIS_PARTICLEEMITTER_HPP

#include <vector>
#include "Position.hpp"

struct Particle {
	bool alive;
	Position pivot;
	std::string texture;
};

class ParticleEmitter {
public:

private:
	std::vector<Particle> particles;
	Position pivot;

};

#endif // TETRIS_PARTICLEEMITTER_HPP
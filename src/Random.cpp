#include "Random.hpp"

std::random_device Random::randomSeed;
std::default_random_engine Random::randomEngine( randomSeed() );
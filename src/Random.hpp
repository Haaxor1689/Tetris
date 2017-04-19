#pragma once

#include <random>

class Random {
public:
	static int get(int from, int to) {
		return std::uniform_int_distribution<int>{from, to}.operator()(randomEngine);
	}

	static std::random_device randomSeed;
private:
	static std::default_random_engine randomEngine;
};
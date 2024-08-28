#include "Apple.h"

#include <random>

void Apple::SetSpot(unsigned int x, unsigned int y) {

	//Generate random spot on grid

	//Hardware-based seed
	std::random_device seed;

	//Number engine seeded with seed
	std::mt19937 gen{ seed() };

	//Set number distribution uniform and pass in range
	std::uniform_int_distribution<> dist{ static_cast<int>(x - 1), static_cast<int>(y - 1) };

	m_spot[0] = dist(gen);
	m_spot[1] = dist(gen);
}
#include "Apple.h"

#include <random>
#include <algorithm>

void Apple::SetSpot(Renderer::Grid& grid, Snake& snake) {

	GenerateSpot(grid, snake);
	grid.SetPixel(m_spot[0], m_spot[1], { 1.f, 0.f, 0.f, 1.f }, true);
	
}

void Apple::GenerateSpot(Renderer::Grid& grid, Snake& snake) {
	unsigned int randomX, randomY;

	//Generate random spot on grid

	//Hardware-based seed
	std::random_device seed;

	//Number engine seeded with seed
	std::mt19937 gen{ seed() };

	//Set number distribution uniform and pass in range
	std::uniform_int_distribution<> distX{ 0, static_cast<int>(grid.GetSizeX() - 1) };
	std::uniform_int_distribution<> distY{ 0, static_cast<int>(grid.GetSizeY() - 1) };

	while (true) {
		randomX = distX(gen);
		randomY = distY(gen);

		//Check if generated value already exists
		if (std::find(snake.GetPoints().begin(), snake.GetPoints().end(), std::make_tuple(randomX, randomY)) == snake.GetPoints().end()) {
			m_spot[0] = randomX;
			m_spot[1] = randomY;
			break;
		}
	}
}

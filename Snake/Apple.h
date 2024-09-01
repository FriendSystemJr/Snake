#pragma once
#include <array>

#include "Grid.h"
#include "Snake.h"

class Apple {
public:

	Apple() = default;

	//Setter
	void SetSpot(Renderer::Grid& grid, Snake& snake);
private:

	//Functions
	void GenerateSpot(Renderer::Grid& grid, Snake& snake);

	std::array<unsigned int, 2> m_spot;
};
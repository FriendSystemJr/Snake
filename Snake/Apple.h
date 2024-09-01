#pragma once
#include <array>

#include "Grid.h"

class Snake;

class Apple {
public:

	Apple() = default;

	//Getter
	std::array<unsigned int, 2>& GetSpot();

	//Setter
	void SetSpot(Renderer::Grid& grid, Snake& snake);
private:

	//Functions
	void GenerateSpot(Renderer::Grid& grid, Snake& snake);

	std::array<unsigned int, 2> m_spot;
};
#pragma once
#include <vector>
#include <tuple>

#include "Grid.h"

class Snake {
public:
	Snake();

	enum directions {
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3,
	};

	//Functions
	void SetPixels(Renderer::Grid& grid);
	void Move(directions direction, Renderer::Grid& grid);

private:
	float m_velocity;
	
	std::vector<std::tuple<int, int>> m_points;
	directions m_direction;

};
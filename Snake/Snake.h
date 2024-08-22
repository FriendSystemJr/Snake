#pragma once
#include <deque>
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

	//Setter
	void SetDirection(directions direction);

	//Functions
	void SetPixels(Renderer::Grid& grid);
	void Move(directions direction, Renderer::Grid& grid);

private:
	float m_velocity;
	
	std::deque<std::tuple<int, int>> m_points;
	directions m_direction;

};
#pragma once
#include <deque>
#include <tuple>

#include "RenderAPI.h"
#include "Apple.h"

class Snake {
public:
	Snake();

	enum directions {
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3,
	};

	//Getter
	std::deque<std::tuple<int, int>>& GetPoints();

	//Setter
	void SetDirection(directions direction);

	//Functions
	void SetPixels(Renderer::Grid& grid);
	void Move(Renderer::Grid& grid);
	void CollisionDetect(Apple& apple);

private:
	float m_velocity;
	float m_movement;

	std::deque<std::tuple<int, int>> m_points;
	directions m_direction;

};
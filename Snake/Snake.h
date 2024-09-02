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

	enum state {
		START,
		GAME,
		END,
	};

	//Getter
	std::deque<std::tuple<int, int>>& GetPoints();
	state GetState();

	//Setter
	void SetDirection(directions direction);
	void SetState(state state);

	//Functions
	void SetPixels(Renderer::Grid& grid);
	void Move(Renderer::Grid& grid);
	void CollisionDetect(Apple& apple);

private:
	float m_velocity;
	float m_movement;

	std::deque<std::tuple<int, int>> m_points;

	directions m_direction;
	state m_state;

};
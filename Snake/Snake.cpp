#include "Snake.h"

Snake::Snake() {
	
	m_velocity = 3.5f;
	m_movement = 0.f;

	m_direction = RIGHT;

	m_state = START;

	m_points.push_back({ 10, 10 });
	m_points.push_back({ 9, 10 });
	m_points.push_back({ 8, 10 });
	m_points.push_back({ 7, 10 });
	
}

void Snake::SetPixels(Renderer::Grid& grid) {
	for (int i = 0; i < m_points.size(); ++i) {
		if (i == 0) {
			grid.SetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]), { 1.f, 0.f, 0.929f, 1.0f }, true);
			continue;
		}
		grid.SetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]), {0.071f, 0.922f, 0.369f, 1.0f}, true);
	}
}

void Snake::CollisionDetect(Apple& apple) {

	if (std::find(m_points.begin() + 1, m_points.end(), m_points.front()) != m_points.end()) {
		std::cout << "Crashed!\n";
		m_state = END;
		return;
	}

	if (m_points.front() == std::make_tuple(apple.GetSpot()[0], apple.GetSpot()[1])) {

		//Check if last two points are on the same x-axis
		if (std::get<0>(m_points.back()) - std::get<0>(m_points[m_points.size() - 2]) == 0) {
			//Check if second last element is above or under last element
			//and push back new point based on that
			if (std::get<1>(m_points.back()) - std::get<1>(m_points[m_points.size() - 2]) == -1) {
				m_points.push_back({ std::get<0>(m_points.back()), std::get<1>(m_points.back()) - 1 });
			}
			else if (std::get<1>(m_points.back()) - std::get<1>(m_points[m_points.size() - 2]) == 1) {
				m_points.push_back({ std::get<0>(m_points.back()), std::get<1>(m_points.back()) + 1 });
			}
		}
		//Check if last two points are on the same y-axis
		else if (std::get<1>(m_points.back()) - std::get<1>(m_points[m_points.size() - 2]) == 0) {
			//Check position of second last element relative to the last element
			if (std::get<0>(m_points.back()) - std::get<0>(m_points[m_points.size() - 2]) == -1) {
				m_points.push_back({ std::get<0>(m_points.back()) - 1, std::get<1>(m_points.back()) });
			}
			else if (std::get<0>(m_points.back()) - std::get<0>(m_points[m_points.size() - 2]) == 1) {
				m_points.push_back({ std::get<0>(m_points.back()) + 1, std::get<1>(m_points.back()) });
			}
		}
		//Remove apple
		apple.GetSpot()[0] = -1;
	}
}

void Snake::Move(Renderer::Grid& grid) {
	if (m_movement > 1) {
		if (m_direction == UP) {

			grid.UnsetPixel(std::get<0>(m_points.back()), std::get<1>(m_points.back()));
			m_points.pop_back();
			m_points.push_front({ std::get<0>(m_points.front()), std::get<1>(m_points.front()) + 1 });

			m_movement = 0.f;

		}
		else if (m_direction == RIGHT) {

			grid.UnsetPixel(std::get<0>(m_points.back()), std::get<1>(m_points.back()));
			m_points.pop_back();
			m_points.push_front({ std::get<0>(m_points.front()) + 1, std::get<1>(m_points.front()) });
			m_movement = 0.f;

		}
		else if (m_direction == DOWN) {
			grid.UnsetPixel(std::get<0>(m_points.back()), std::get<1>(m_points.back()));
			m_points.pop_back();
			m_points.push_front({ std::get<0>(m_points.front()), std::get<1>(m_points.front()) - 1 });
			m_movement = 0.f;
		}
		else if (m_direction == LEFT) {
			grid.UnsetPixel(std::get<0>(m_points.back()), std::get<1>(m_points.back()));
			m_points.pop_back();
			m_points.push_front({ std::get<0>(m_points.front()) - 1, std::get<1>(m_points.front()) });
			m_movement = 0.f;
		}
	}
	else {
		m_movement += m_velocity * Renderer::GetDeltaTime();
	}
}

//Getter
std::deque<std::tuple<int, int>>& Snake::GetPoints() {
	return m_points;
}

Snake::state Snake::GetState() {
	return m_state;
}

//Setter
void Snake::SetDirection(directions direction) {

	if (m_state == START && direction != LEFT)
		m_state = GAME;

	if (m_direction == direction)
		return;

	//Check if pixels are on the same x-axis
	if (std::get<0>(m_points.front()) - std::get<0>(m_points[1]) == 0) {

		//Check y-axis for the case that second pixel is under first pixel
		if (std::get<1>(m_points.front()) - std::get<1>(m_points[1]) == 1) {
			if (direction == DOWN) {
				return;
			}
			m_direction = direction;
		}

		//Check y-axis for the case that second pixel is above first pixel
		else if (std::get<1>(m_points.front()) - std::get<1>(m_points[1]) == -1) {
			if (direction == UP) {
				return;
			}
			m_direction = direction;
		}
	}

	//Check if pixels are on the same y-axis
	else if (std::get<1>(m_points.front()) - std::get<1>(m_points[1]) == 0) {
		//Check x-axis for the case that second pixel is left from first pixel
		if (std::get<0>(m_points.front()) - std::get<0>(m_points[1]) == 1) {
			if (direction == LEFT) {
				return;
			}
			m_direction = direction;
		}

		//Check x-axis for the case that second pixel is right from first pixel
		else if (std::get<0>(m_points.front()) - std::get<0>(m_points[1]) == -1) {
			if (direction == RIGHT) {
				return;
			}
			m_direction = direction;
		}
	}


}

void Snake::SetState(state state) {
	m_state = state;
}
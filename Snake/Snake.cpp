#include "Snake.h"

Snake::Snake() {
	//TODO: change velocity
	m_velocity = 3.5f;
	m_movement = 0.f;

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

void Snake::Move(Renderer::Grid& grid) {
	if (m_movement > 1) {
		if (m_direction == UP) {
			/*for (int i = 0; i < m_points.size(); ++i) {
				grid.UnsetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]));
				std::get<1>(m_points[i]) += 1;
			}*/

			grid.UnsetPixel(std::get<0>(m_points.back()), std::get<1>(m_points.back()));
			m_points.pop_back();
			m_points.push_front({ std::get<0>(m_points.front()), std::get<1>(m_points.front()) + 1 });

			m_movement = 0.f;

		}
		else if (m_direction == RIGHT) {
			/*for (int i = 0; i < m_points.size(); ++i) {
				grid.UnsetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]));
				std::get<0>(m_points[i]) += 1;
			}*/

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

//Setter
void Snake::SetDirection(directions direction) {
	m_direction = direction;
}
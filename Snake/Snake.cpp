#include "Snake.h"

Snake::Snake() {
	//TODO: change velocity
	m_velocity = 1.0f;

	//m_points.push_back({ 10, 10 });
	//m_points.push_back({ 9, 10 });

	m_points.push_back({ 10, 10 });
	m_points.push_back({ 9, 10 });
	m_points.push_back({ 8, 10 });
	m_points.push_back({ 7, 10 });
	
}

void Snake::SetPixels(Renderer::Grid& grid) {
	for (int i = 0; i < m_points.size(); ++i) {
		if (i == 0) {
			grid.SetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]), { 1.f, 0.f, 0.929f, 1.0f });
			continue;
		}
		grid.SetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]), {0.071f, 0.922f, 0.369f, 1.0f});
	}
}

/*TODO: Rework logic so when multiple pixels are set only the last and the first one change on the grid (with set/unset)*/
void Snake::Move(directions direction, Renderer::Grid& grid) {
	if (direction == UP) {
		/*for (int i = 0; i < m_points.size(); ++i) {
			grid.UnsetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]));
			std::get<1>(m_points[i]) += 1;
		}*/

		grid.UnsetPixel(std::get<0>(m_points.back()), std::get<1>(m_points.back()));
		m_points.pop_back();
		m_points.push_front({ std::get<0>(m_points.front()), std::get<1>(m_points.front()) + 1 });

	}
	else if (direction == RIGHT) {
		/*for (int i = 0; i < m_points.size(); ++i) {
			grid.UnsetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]));
			std::get<0>(m_points[i]) += 1;
		}*/

		grid.UnsetPixel(std::get<0>(m_points.back()), std::get<1>(m_points.back()));
		m_points.pop_back();
		m_points.push_front({ std::get<0>(m_points.front()) + 1, std::get<1>(m_points.front()) });

	}
	else if (direction == DOWN) {
		grid.UnsetPixel(std::get<0>(m_points.back()), std::get<1>(m_points.back()));
		m_points.pop_back();
		m_points.push_front({ std::get<0>(m_points.front()), std::get<1>(m_points.front()) - 1 });
	}
	else if (direction == LEFT) {
		grid.UnsetPixel(std::get<0>(m_points.back()), std::get<1>(m_points.back()));
		m_points.pop_back();
		m_points.push_front({ std::get<0>(m_points.front()) - 1, std::get<1>(m_points.front()) });
	}
}
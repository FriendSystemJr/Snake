#include "Snake.h"

Snake::Snake() {
	//TODO: change velocity
	m_velocity = 1.0f;

	m_points.push_back({ 10, 10 });
}

void Snake::SetPixels(Renderer::Grid& grid) {
	for (int i = 0; i < m_points.size(); ++i) {
		grid.SetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]));
	}
}

/*TODO: Rework logic so when multiple pixels are set only the last and the first one change on the grid (with set/unset)*/
void Snake::Move(directions direction, Renderer::Grid& grid) {
	if (direction == UP) {
		for (int i = 0; i < m_points.size(); ++i) {
			grid.UnsetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]));
			std::get<1>(m_points[i]) += 1;
		}
	}
	else if (direction == RIGHT) {
		for (int i = 0; i < m_points.size(); ++i) {
			grid.UnsetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]));
			std::get<0>(m_points[i]) += 1;
		}
	}
	else if (direction == DOWN) {
		for (int i = 0; i < m_points.size(); ++i) {
			grid.UnsetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]));
			std::get<1>(m_points[i]) -= 1;
		}
	}
	else if (direction == LEFT) {
		for (int i = 0; i < m_points.size(); ++i) {
			grid.UnsetPixel(std::get<0>(m_points[i]), std::get<1>(m_points[i]));
			std::get<0>(m_points[i]) -= 1;
		}
	}
}
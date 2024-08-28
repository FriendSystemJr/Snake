#pragma once
#include <array>

class Apple {
public:

	//Setter
	void SetSpot(unsigned int x, unsigned int y);
private:
	std::array<unsigned int, 2> m_spot;
};
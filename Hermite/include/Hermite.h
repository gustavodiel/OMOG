#pragma once

#include "SFML/Graphics.hpp"
#include "Point.h"

class Hermite
{
public:
	Hermite();
	~Hermite();

	void Interpolate(double time, std::vector<Point*> points, sf::Vector2i* result);
};


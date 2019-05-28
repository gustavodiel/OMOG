#pragma once

#include "SFML/Graphics.hpp"
#include "Point.h"
#include "Tangent.h"

class Hermite
{
public:
	Hermite();
	~Hermite();

	void PairInterpolate(double time, Point* pointA, Point* pointB, sf::Vector2i tanA, sf::Vector2i tanB, sf::Vector2i* result);

	void Interpolate(double time, std::vector<Point*> points, sf::Vector2i* result);
};


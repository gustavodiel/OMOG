#pragma once

#include "Entity.h"
#include "Tangent.h"

class Point : public Entity
{
public:
	Tangent *ptrTangent, *ptrTangentSecondary;

	bool showPrimaryTangent = true;
	bool showSecondaryTangent = false;

	Point(double x, double y);
	~Point();

	void MoveTo(double x, double y);
	void Move(double dX, double dY);

	void Draw();

	sf::Vector2i NormalizedTangent(int scale = 5);
	sf::Vector2i NormalizedTangentSecondary(int scale = 5);
};


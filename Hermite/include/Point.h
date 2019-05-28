#pragma once

#include "Entity.h"
#include "Tangent.h"

class Point : public Entity
{
public:
	Tangent *ptrTangent, *ptrTangentSecondary;

	bool showPrimaryTangent = true;
	bool showSecondaryTangent = false;

	Point(int x, int y);
	~Point();

	void MoveTo(int x, int y);
	void Move(int dX, int dY);

	void Draw();

	sf::Vector2i NormalizedTangent(int scale = 5);
	sf::Vector2i NormalizedTangentSecondary(int scale = 5);
};


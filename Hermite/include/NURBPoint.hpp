#pragma once

#include "Entity.h"

class NURBPoint : public Entity
{
public:
	NURBPoint(double x, double y);
	~NURBPoint();

	void MoveTo(double x, double y);
	void Move(double dX, double dY);

	void Draw();
};


#pragma once

#include <iostream>

#include <math.h>

#include "SFML/Graphics.hpp"
#include "ShapesManager.h"

class Entity
{
public:
	int x;
	int y;

	int radius = 25;

	bool selected = false;

	sf::Color color, selectedColor;

	Entity(int x, int y) : x(x), y(y), selected(false) {}
	~Entity() {}

	virtual void MoveTo(int x, int y) {
		this->x = x;
		this->y = y;
	}

	virtual void Move(int dX, int dY) {
		this->x += dX;
		this->y += dY;
	}

	bool IsInside(int x, int y) {
		return this->Distance(x, y) < this->radius;
	}

	float Distance(int x, int y) {
		int xx = (x - this->x) * (x - this->x);
		int yy = (y - this->y) * (y - this->y);

		return sqrt(xx + yy);
	}

	virtual void Draw() {
		ShapesManager::getInstance()->ptrCircleShape->setFillColor(color);

		if (this->selected) {
			ShapesManager::getInstance()->ptrCircleShape->setFillColor(selectedColor);
		}

		ShapesManager::getInstance()->ptrCircleShape->setRadius(this->radius);
		ShapesManager::getInstance()->ptrCircleShape->setPosition(this->x, this->y);
		ShapesManager::getInstance()->ptrCircleShape->setOrigin(this->radius, this->radius);

		ShapesManager::getInstance()->ptrWindow->draw(*ShapesManager::getInstance()->ptrCircleShape);

	}
};

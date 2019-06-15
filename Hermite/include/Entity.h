#pragma once

#include <iostream>

#include <math.h>

#include "SFML/Graphics.hpp"
#include "ShapesManager.h"

#define TYPE double

class Entity
{
public:
	TYPE x;
	TYPE y;

	int radius = 25;

	bool selected = false;

	sf::Color color, selectedColor;

	Entity(TYPE x, TYPE y) : x(x), y(y), selected(false) {}
	~Entity() {}

	virtual void MoveTo(TYPE x, TYPE y) {
		this->x = x;
		this->y = y;
	}

	virtual void Move(TYPE dX, TYPE dY) {
		this->x += dX;
		this->y += dY;
	}

	bool IsInside(TYPE x, TYPE y) {
		return this->Distance(x, y) < this->radius;
	}

	float Distance(TYPE x, TYPE y) {
		TYPE xx = (x - this->x) * (x - this->x);
		TYPE yy = (y - this->y) * (y - this->y);

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

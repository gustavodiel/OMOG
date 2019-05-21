#pragma once

#include "SFML/Graphics.hpp"

class ShapesManager
{
public:

	//sf::RectangleShape      *ptrRectangleShape;
	sf::CircleShape			*ptrCircleShape;

	sf::RenderWindow        *ptrWindow;

	static ShapesManager* getInstance() {
		static ShapesManager instance;

		return &instance;
	}

	ShapesManager(const ShapesManager&) = delete;
	ShapesManager& operator=(const ShapesManager&) = delete;


private:

	ShapesManager() {};
};

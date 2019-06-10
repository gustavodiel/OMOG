#pragma once

#include "SFML/Graphics.hpp"
#include "Point.h"
#include "Tangent.h"

class Hermite
{
private:
	sf::Vector2i last;
	sf::Vector2i point;

	bool tangentForEach = false;

	std::vector<Point*> points;

	Point* lastCreatedPoint;

	Entity* selectedEntity = NULL;
public:
	Hermite();
	~Hermite();

	void PairInterpolate(double time, Point* pointA, Point* pointB, sf::Vector2i tanA, sf::Vector2i tanB, sf::Vector2i* result);

	void Interpolate(double time, std::vector<Point*> points, sf::Vector2i* result);
	void Update();
	void Draw();

	void OnRightMouseClicked(sf::Vector2i position);
	void OnLeftMouseClicked(sf::Vector2i position);
	void OnRightMouseReleased(sf::Vector2i position);
	void OnLeftMouseReleased(sf::Vector2i position);
	void OnRightMouseDragged(sf::Vector2i position);
	void OnLeftMouseDragged(sf::Vector2i position);

	Entity* EntityInMousePosition(int x, int y);
};


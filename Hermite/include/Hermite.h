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

	bool hidePoints = false;
public:
	Hermite();
	~Hermite();

	void PairInterpolate(double time, Point* pointA, Point* pointB, sf::Vector2i tanA, sf::Vector2i tanB, sf::Vector2i* result);

	void Interpolate(double time, sf::Vector2i* result);
	void Update();
	void Draw();

	bool OnRightMouseClicked(sf::Vector2i position);
	bool OnLeftMouseClicked(sf::Vector2i position);
	bool OnRightMouseReleased(sf::Vector2i position);
	bool OnLeftMouseReleased(sf::Vector2i position);
	bool OnRightMouseDragged(sf::Vector2i position);
	bool OnLeftMouseDragged(sf::Vector2i position);

	Entity* EntityInMousePosition(int x, int y);
	Point* FirstPoint();
	void ToggleHidePoints();
	bool IsReady();
};


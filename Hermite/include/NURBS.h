#pragma once

#include "SFML/Graphics.hpp"
#include "../include/NURBPoint.hpp"
#include "../include/Point.h"

class NURBS {
private:
	sf::Vector2i last;

	std::vector<NURBPoint*> points;

	NURBPoint* lastCreatedPoint;

	Entity* selectedEntity = NULL;

	Point* target = NULL;
	sf::Vector2i secondTarget;

	double velX = 0, velY = 0;
	double velX2 = 0, velY2 = 0;

	bool hidePoints = false;;
public:
	NURBS();
	~NURBS();

	void Interpolate(double time, sf::Vector2i* result);
	void Update();
	void Draw();

	void SetTarget(Point* point, double time);

	bool OnRightMouseClicked(sf::Vector2i position);
	bool OnLeftMouseClicked(sf::Vector2i position);
	bool OnRightMouseReleased(sf::Vector2i position);
	bool OnLeftMouseReleased(sf::Vector2i position);
	bool OnRightMouseDragged(sf::Vector2i position);
	bool OnLeftMouseDragged(sf::Vector2i position);

	Entity* EntityInMousePosition(int x, int y);
	void ToggleHidePoints();
	bool IsReady();
};
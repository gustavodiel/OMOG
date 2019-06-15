#include "../include/NURBPoint.hpp"

NURBPoint::NURBPoint(double x, double y) : Entity(x, y)
{
	this->radius = 20;

	this->color = sf::Color::Cyan;
	this->selectedColor = sf::Color::White;
}


NURBPoint::~NURBPoint()
{
}

void NURBPoint::MoveTo(double x, double y) {
	int diffX = x - this->x;
	int diffY = y - this->y;

	Entity::MoveTo(x, y);
}

void NURBPoint::Move(double dX, double dY) {
	Entity::Move(dX, dY);
}

void NURBPoint::Draw() {
	Entity::Draw();
}

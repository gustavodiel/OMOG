#include "../include/Point.h"



Point::Point(int x, int y) : Entity(x, y)
{
	this->radius = 25;

	this->ptrTangent = new Tangent(x, y - 100);

	this->color = sf::Color::Green;
	this->selectedColor = sf::Color::White;
}


Point::~Point()
{
}

void Point::MoveTo(int x, int y) {
	int diffX = x - this->x;
	int diffY = y - this->y;

	this->ptrTangent->Move(diffX, diffY);

	Entity::MoveTo(x, y);
}

void Point::Move(int dX, int dY) {
	this->ptrTangent->Move(dX, dY);

	Entity::Move(dX, dY);
}

void Point::Draw() {

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(this->x, this->y)),
		sf::Vertex(sf::Vector2f(this->ptrTangent->x, this->ptrTangent->y))
	};

	ShapesManager::getInstance()->ptrWindow->draw(line, 2, sf::Lines);

	Entity::Draw();
	this->ptrTangent->Draw();
}

sf::Vector2i Point::NormalizedTangent(int scale /*= 5*/)
{

	sf::Vector2i newTangent(this->ptrTangent->x - this->x, this->ptrTangent->y - this->y);

	newTangent.x *= scale;
	newTangent.y *= scale;

	return newTangent;

}

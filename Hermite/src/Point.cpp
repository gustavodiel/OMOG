#include "../include/Point.h"



Point::Point(int x, int y) : Entity(x, y)
{
	this->radius = 25;

	this->ptrTangent = new Tangent(x, y - 100);
	this->ptrTangentSecondary = new Tangent(x, y + 100);
	this->ptrTangentSecondary->color = sf::Color(0, 255, 255);

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
	this->ptrTangentSecondary->Move(diffX, diffY);

	Entity::MoveTo(x, y);
}

void Point::Move(int dX, int dY) {
	this->ptrTangent->Move(dX, dY);
	this->ptrTangentSecondary->Move(dX, dY);

	Entity::Move(dX, dY);
}

void Point::Draw() {
	Entity::Draw();

	if (showPrimaryTangent) {
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(this->x, this->y)),
			sf::Vertex(sf::Vector2f(this->ptrTangent->x, this->ptrTangent->y))
		};

		ShapesManager::getInstance()->ptrWindow->draw(line, 2, sf::Lines);
		this->ptrTangent->Draw();
	}

	if (showSecondaryTangent) {
		sf::Vertex line_secondary[] =
		{
			sf::Vertex(sf::Vector2f(this->x, this->y)),
			sf::Vertex(sf::Vector2f(this->ptrTangentSecondary->x, this->ptrTangentSecondary->y))
		};

		ShapesManager::getInstance()->ptrWindow->draw(line_secondary, 2, sf::Lines);
		this->ptrTangentSecondary->Draw();
	}
}

sf::Vector2i Point::NormalizedTangent(int scale /*= 5*/)
{

	sf::Vector2i newTangent(this->ptrTangent->x - this->x, this->ptrTangent->y - this->y);

	newTangent.x *= scale;
	newTangent.y *= scale;

	return newTangent;

}


sf::Vector2i Point::NormalizedTangentSecondary(int scale /*= 5*/)
{

	sf::Vector2i newTangent(this->ptrTangentSecondary->x - this->x, this->ptrTangentSecondary->y - this->y);

	newTangent.x *= scale;
	newTangent.y *= scale;

	return newTangent;

}

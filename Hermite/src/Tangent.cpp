#include "../include/Tangent.h"



Tangent::Tangent(int x, int y) : Entity(x, y)
{
	this->radius = 15;

	this->color = sf::Color::Red;
	this->selectedColor = sf::Color::White;
}


Tangent::~Tangent()
{
}

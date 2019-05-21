//
// Created by d on 18/03/19.
//

#include "../include/Application.hpp"
#include "../build/Hermite.h"


Application::Application(MAP_TYPE _x, MAP_TYPE _y) :
    windowX(_x), windowY(_y) { }

void Application::Start() {
    this->ptrWindow = new sf::RenderWindow(sf::VideoMode(windowX, windowY), "OMOG - Trabalho 1 - Hermite - Gustavo Diel");

    //this->ptrWindow->setFramerateLimit(10);

	ShapesManager::getInstance()->ptrWindow = ptrWindow;
	ShapesManager::getInstance()->ptrCircleShape = new sf::CircleShape();

	Hermite hermite;

	points.push_back(new Point(500, 500));

	sf::Clock clock;

	bool justRightClicked = false;

	bool justLeftClicked = false;

	sf::Vector2i last;

	sf::Vector2i point;

    while (this->ptrWindow->isOpen())
    {
        sf::Event event;
		while (this->ptrWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->ptrWindow->close();
		}

		// float ElapsedTime = clock.getElapsedTime().asSeconds();
		// clock.restart();

		sf::Vector2i position = sf::Mouse::getPosition(*ptrWindow);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!justLeftClicked) {
				justLeftClicked = true;
				this->OnLeftMouseClicked(position);
			}
			else {
				this->OnLeftMouseDragged(position);
			}
		}
		else {
			if (justLeftClicked) {
				this->OnLeftMouseReleased(position);
				justLeftClicked = false;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			if (!justRightClicked) {
				justRightClicked = true;
				this->OnRightMouseClicked(position);
			}
			else {
				this->OnRightMouseDragged(position);
			}
		}
		else {
			if (justRightClicked) {
				this->OnRightMouseReleased(position);
				justRightClicked = false;
			}
		}

		this->ptrWindow->clear();

		/// CALCUALTE HERMITE

		if (points.size() > 1) {
			last = sf::Vector2i(points.at(0)->x, points.at(0)->y);

			for (double i = 0; i < 1; i += 0.001) {
				hermite.Interpolate(i, points, &point);

				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(last.x, last.y)),
					sf::Vertex(sf::Vector2f(point.x, point.y))
				};

				last = point;

				ShapesManager::getInstance()->ptrWindow->draw(line, 2, sf::Lines);

			}
		}

		/// END

		for (auto point : points) {
			point->Draw();
		}

		this->ptrWindow->display();

		// printf("Frame took %5lf\n", ElapsedTime);
    }
}



void Application::ProcessLoop() {

}

void Application::OnRightMouseClicked(sf::Vector2i position)
{
	points.push_back(new Point(position.x, position.y));
}

void Application::OnLeftMouseClicked(sf::Vector2i position)
{
	if (selectedEntity != NULL) {
		selectedEntity->selected = false;
	}

	selectedEntity = this->EntityInMousePosition(position.x, position.y);

	if (selectedEntity != NULL) {
		selectedEntity->selected = true;
	}
}

void Application::OnRightMouseReleased(sf::Vector2i position)
{

}

void Application::OnLeftMouseReleased(sf::Vector2i position)
{
	if (selectedEntity != NULL) {
		selectedEntity->selected = false;
		selectedEntity = NULL;
	}
}

void Application::OnRightMouseDragged(sf::Vector2i position)
{

}

void Application::OnLeftMouseDragged(sf::Vector2i position)
{
	if (selectedEntity != NULL) {
		selectedEntity->MoveTo(position.x, position.y);
	}
}

Entity* Application::EntityInMousePosition(int x, int y)
{
	for (auto point : points) {
		if (point->IsInside(x, y)) {
			return point;
		}
		if (point->ptrTangent->IsInside(x, y)) {
			return point->ptrTangent;
		}
	}

	return NULL;
}

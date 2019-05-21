//
// Created by d on 18/03/19.
//

#ifndef ANTS_APPLICATION_H
#define ANTS_APPLICATION_H

#include <SFML/Graphics.hpp>
#include "Defines.hpp"
#include "../build/Point.h"
#include "../build/Entity.h"

class Application {
public:

    MAP_TYPE windowX, windowY;

    Application(MAP_TYPE _x, MAP_TYPE _y);

    void Start();

private:

    sf::RenderWindow        *ptrWindow;

    void ProcessLoop();

	void OnRightMouseClicked(sf::Vector2i position);
	void OnLeftMouseClicked(sf::Vector2i position);

	void OnRightMouseReleased(sf::Vector2i position);
	void OnLeftMouseReleased(sf::Vector2i position);

	void OnRightMouseDragged(sf::Vector2i position);
	void OnLeftMouseDragged(sf::Vector2i position);

	Entity* EntityInMousePosition(int x, int y);

	std::vector<Point*> points;

	Entity* selectedEntity = NULL;

};


#endif //ANTS_APPLICATION_H

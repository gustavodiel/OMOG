//
// Created by d on 18/03/19.
//

#ifndef ANTS_APPLICATION_H
#define ANTS_APPLICATION_H

#include <SFML/Graphics.hpp>
#include "Defines.hpp"
#include "../include/Point.h"
#include "../include/Entity.h"
#include  "../include/Hermite.h"

class Application {
public:	
    MAP_TYPE windowX, windowY;

    Application(MAP_TYPE _x, MAP_TYPE _y);

    void Start();

	Hermite* hermite = new Hermite();

private:
	sf::RenderWindow        *ptrWindow;

	sf::Text text;
	bool isHermite = true;
	bool disableSpace = false;

    void ProcessLoop();

	void OnRightMouseClicked(sf::Vector2i position);
	void OnLeftMouseClicked(sf::Vector2i position);

	void OnRightMouseReleased(sf::Vector2i position);
	void OnLeftMouseReleased(sf::Vector2i position);

	void OnRightMouseDragged(sf::Vector2i position);
	void OnLeftMouseDragged(sf::Vector2i position);

	Entity* EntityInMousePosition(int x, int y);
public:
	void OnSpacePressed();
	void OnSpaceHold();
	void OnSpaceReleased();
	void OnEnterPressed();
	void OnEnterReleased();
};


#endif //ANTS_APPLICATION_H

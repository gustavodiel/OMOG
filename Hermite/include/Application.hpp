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
#include "../include/NURBS.h"

class Application {
private:
	typedef enum
	{
		DRAWING_HERMITE,
		DRAWING_NURBS,
		ANIMATION,
		STOPPED
	} States;


public:	
    MAP_TYPE windowX, windowY;

    Application(MAP_TYPE _x, MAP_TYPE _y);

    void Start();

	void HandleInput();

	Hermite* hermite = new Hermite();
	NURBS*   nurbs   = new NURBS();

private:
	sf::RenderWindow        *ptrWindow;


	sf::Clock clock;

	sf::Font font;

	sf::Text text;
	sf::Text pressPToHidePoints;
	sf::Text pressSpaceToToggle;
	sf::Text pressEnterToJoin;


	bool disableSpace = false;

	States state = DRAWING_HERMITE;

	bool justRightClicked = false;
	bool justLeftClicked = false;
	bool spacePressed = false;
	bool enterPressed = false;
	bool pPressed = false;

    void ProcessLoop();

	void OnRightMouseClicked(sf::Vector2i position);
	void OnLeftMouseClicked(sf::Vector2i position);

	void OnRightMouseReleased(sf::Vector2i position);
	void OnLeftMouseReleased(sf::Vector2i position);

	void OnRightMouseDragged(sf::Vector2i position);
	void OnLeftMouseDragged(sf::Vector2i position);

	bool LockedForInteract() {
		return state == STOPPED || state == ANIMATION;
	}

public:
	void OnSpacePressed();
	void OnSpaceHold();
	void OnSpaceReleased();

	void SetDrawingNurbs();

	void SetDrawingHermite();

	void OnEnterPressed();
	void OnEnterReleased();
	void OnPPressed();
	void OnPReleased();
};


#endif //ANTS_APPLICATION_H

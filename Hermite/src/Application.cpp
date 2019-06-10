//
// Created by d on 18/03/19.
//

#include "../include/Application.hpp"
#include "../include/Hermite.h"


Application::Application(MAP_TYPE _x, MAP_TYPE _y) :
    windowX(_x), windowY(_y) { }

void Application::Start() {
    this->ptrWindow = new sf::RenderWindow(sf::VideoMode(windowX, windowY), "OMOG - Trabalho 1 - Hermite - Gustavo Diel");

    //this->ptrWindow->setFramerateLimit(10);

	ShapesManager::getInstance()->ptrWindow = ptrWindow;
	ShapesManager::getInstance()->ptrCircleShape = new sf::CircleShape();

	sf::Clock clock;

	bool justRightClicked = false;
	bool justLeftClicked = false;
	bool spacePressed = false;
	bool enterPressed = false;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		perror("Failed to load font!");
		exit(-5);
	}

	text.setFont(font);	
	text.setString("Hermite");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    while (this->ptrWindow->isOpen())
    {
        sf::Event event;
		while (this->ptrWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->ptrWindow->close();
		}

		float ElapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (!spacePressed) {
				spacePressed = true;
				this->OnSpacePressed();
			}
			else {
				this->OnSpaceHold();
			}
		}
		else {
			if (spacePressed) {
				spacePressed = false;
				this->OnSpaceReleased();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			if (!enterPressed) {
				enterPressed = true;
				this->OnEnterPressed();
			}
		}
		else {
			if (enterPressed) {
				enterPressed = false;
				this->OnEnterReleased();
			}
		}

		this->ptrWindow->clear();

		this->hermite->Update();
		this->hermite->Draw();

		this->ptrWindow->draw(text);

		this->ptrWindow->display();

		//printf("Frame took %5lfs\n", ElapsedTime);
  }
}

void Application::ProcessLoop() {

}

void Application::OnRightMouseClicked(sf::Vector2i position)
{
	if (this->isHermite) {
		hermite->OnRightMouseClicked(position);
	}
	else {

	}
}

void Application::OnLeftMouseClicked(sf::Vector2i position)
{
	if (this->isHermite) {
		hermite->OnLeftMouseClicked(position);
	}
	else {

	}
}

void Application::OnRightMouseReleased(sf::Vector2i position)
{
	if (this->isHermite) {
		hermite->OnRightMouseReleased(position);
	}
	else {

	}
}

void Application::OnLeftMouseReleased(sf::Vector2i position)
{
	if (this->isHermite) {
		hermite->OnLeftMouseReleased(position);
	}
	else {

	}
}

void Application::OnRightMouseDragged(sf::Vector2i position)
{
	if (this->isHermite) {
		hermite->OnRightMouseDragged(position);
	}
	else {

	}
}

void Application::OnLeftMouseDragged(sf::Vector2i position)
{
	if (this->isHermite) {
		hermite->OnLeftMouseDragged(position);
	}
	else {

	}
}

void Application::OnSpacePressed()
{
	if (this->disableSpace) return;

	if (this->isHermite) {
		this->isHermite = false;
		this->text.setString("NURBS");
	}
	else {
		this->isHermite = true;
		this->text.setString("Hermite");
	}
}

void Application::OnSpaceHold()
{
}

void Application::OnSpaceReleased()
{
}

void Application::OnEnterPressed()
{
	if (!this->isHermite) {
		disableSpace = true;
		this->text.setString("Joining!");
	}
}

void Application::OnEnterReleased()
{
}

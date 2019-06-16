//
// Created by d on 18/03/19.
//

#include "../include/Application.hpp"
#include "../include/Hermite.h"

#include "../include/ThreadPool.hpp"

Application::Application(MAP_TYPE _x, MAP_TYPE _y) :
    windowX(_x), windowY(_y) { }

void Application::Start() {
    this->ptrWindow = new sf::RenderWindow(sf::VideoMode(windowX, windowY), "OMOG - Trabalho Final - Hermite e Nurbs - Gustavo Diel");

    //this->ptrWindow->setFramerateLimit(10);

	ShapesManager::getInstance()->ptrWindow = ptrWindow;
	ShapesManager::getInstance()->ptrCircleShape = new sf::CircleShape();

	if (!font.loadFromFile("arial.ttf")) {
		perror("Failed to load font!");
		exit(-5);
	}

	text.setFont(font);
	text.setString("DRAWING: Hermite");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Green);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	{
		pressPToHidePoints.setFont(font);
		pressPToHidePoints.setString("Press P to hide points");
		pressPToHidePoints.setCharacterSize(16);
		pressPToHidePoints.setFillColor(sf::Color::White);
		pressPToHidePoints.setPosition(this->windowX - 160, 0);

		pressSpaceToToggle.setFont(font);
		pressSpaceToToggle.setString("Press SPACE to toggle curves");
		pressSpaceToToggle.setCharacterSize(16);
		pressSpaceToToggle.setFillColor(sf::Color::White);
		pressSpaceToToggle.setPosition(this->windowX - 220, 22);

		pressEnterToJoin.setFont(font);
		pressEnterToJoin.setString("Press ENTER to joing them");
		pressEnterToJoin.setCharacterSize(16);
		pressEnterToJoin.setFillColor(sf::Color::White);
		pressEnterToJoin.setPosition(this->windowX - 202, 44);
	}
	std::future<void> hermiteThread;
	std::future<void> nurbsThread;

	ThreadPool::thread_pool pool(2);

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

		HandleInput();

		this->ptrWindow->clear();

		hermiteThread = pool.push([this](int) { this->hermite->Update(); });
		nurbsThread = pool.push([this](int) { this->nurbs->Update(); });
		
		hermiteThread.wait();
		nurbsThread.wait();

		this->hermite->Draw();
		this->nurbs->Draw();

		this->ptrWindow->draw(text);
		this->ptrWindow->draw(pressPToHidePoints);
		this->ptrWindow->draw(pressSpaceToToggle);
		this->ptrWindow->draw(pressEnterToJoin);

		this->ptrWindow->display();

		printf("Frame took %5lfs\n", ElapsedTime);
  }
}

void Application::HandleInput()
{
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		if (!pPressed) {
			pPressed = true;
			this->OnPPressed();
		}
	}
	else {
		if (pPressed) {
			pPressed = false;
			this->OnPReleased();
		}
	}
}

void Application::ProcessLoop() {

}

void Application::OnRightMouseClicked(sf::Vector2i position)
{
	if (this->LockedForInteract()) return;

	if (this->state == DRAWING_HERMITE) this->hermite->OnRightMouseClicked(position);
	if (this->state == DRAWING_NURBS) this->nurbs->OnRightMouseClicked(position);
}

void Application::OnLeftMouseClicked(sf::Vector2i position)
{
	if (this->LockedForInteract()) return;


	if (hermite->OnLeftMouseClicked(position)) {
		this->SetDrawingHermite();
	}
	else {
		if (nurbs->OnLeftMouseClicked(position)) {
			this->SetDrawingNurbs();
		}
	}
}

void Application::OnRightMouseReleased(sf::Vector2i position)
{
	if (this->LockedForInteract()) return;

	if (this->state == DRAWING_HERMITE) hermite->OnRightMouseReleased(position);
	if (this->state == DRAWING_NURBS) nurbs->OnRightMouseReleased(position);
}

void Application::OnLeftMouseReleased(sf::Vector2i position)
{
	if (this->LockedForInteract()) return;

	if (hermite->OnLeftMouseReleased(position)) {
		this->SetDrawingHermite();
	}
	else {
		if (nurbs->OnLeftMouseReleased(position)) {
			this->SetDrawingNurbs();
		}
	}
}

void Application::OnRightMouseDragged(sf::Vector2i position)
{
	if (this->LockedForInteract()) return;

	if (this->state == DRAWING_HERMITE) hermite->OnRightMouseDragged(position);
	if (this->state == DRAWING_NURBS) nurbs->OnRightMouseDragged(position);
}

void Application::OnLeftMouseDragged(sf::Vector2i position)
{
	if (this->LockedForInteract()) return;

	if (!hermite->OnLeftMouseDragged(position))
		nurbs->OnLeftMouseDragged(position);
}

void Application::OnSpacePressed()
{
	if (this->disableSpace) return;
}

void Application::OnSpaceHold()
{
}

void Application::OnSpaceReleased()
{
	switch (this->state)
	{
	case DRAWING_HERMITE:
		SetDrawingNurbs();

		break;

	case DRAWING_NURBS:
		SetDrawingHermite();

		break;
	}
}

void Application::SetDrawingNurbs()
{
	this->text.setString("DRAWING: NURBS");
	this->text.setFillColor(sf::Color::Cyan);
	this->state = DRAWING_NURBS;
}

void Application::SetDrawingHermite()
{
	this->text.setString("DRAWING: Hermite");
	this->text.setFillColor(sf::Color::Green);
	this->state = DRAWING_HERMITE;
}

void Application::OnEnterPressed()
{
	if (this->state == DRAWING_HERMITE || this->state == DRAWING_NURBS) {
		if (!this->hermite->IsReady() || !this->nurbs->IsReady()) return;

		disableSpace = true;
		this->state = ANIMATION;
		this->text.setString("Joining...");
		this->text.setFillColor(sf::Color::Red);

		this->pressEnterToJoin.setString("Press ENTER to reset");

		this->nurbs->SetTarget(this->hermite->FirstPoint(), 2);
	}
	else if (this->state == ANIMATION) {
		this->hermite = new Hermite();
		this->nurbs = new NURBS();

		this->state = DRAWING_HERMITE;
		this->text.setFillColor(sf::Color::Green);
		this->text.setString("DRAWING: Hermite");

		this->pressEnterToJoin.setString("Press ENTER to joing them");
	}
}

void Application::OnEnterReleased()
{
}

void Application::OnPPressed()
{

}

void Application::OnPReleased()
{
	this->hermite->ToggleHidePoints();
	this->nurbs->ToggleHidePoints();
}

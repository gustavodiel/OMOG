#include "../include/NURBS.h"

NURBS::NURBS()
{
	auto firstPoint = new NURBPoint(500, 700);

	lastCreatedPoint = firstPoint;

	points.push_back(firstPoint);
}


NURBS::~NURBS()
{
}

void NURBS::Draw() {
	if (!this->hidePoints) {
		for (auto point : this->points) {
			point->Draw();
		}
	}

	if (lines.size() < 1) {
		return;
	}

	ShapesManager::getInstance()->ptrWindow->draw(lines.data(), lines.size(), sf::LinesStrip);
}

void NURBS::SetTarget(Point* point, double time)
{
	auto firstPoint = this->points.at(0);
	auto secondPoint = this->points.at(1);

	this->target = point;

	sf::Vector2i myPos(point->NormalizedTangent(5) * -1);
	myPos.x += target->x;
	myPos.y += target->y;

	this->secondTarget = myPos;


	velX = (this->target->x - firstPoint->x) / 50.0;
	velY = (this->target->y - firstPoint->y) / 50.0;


	velX2 = (this->secondTarget.x - secondPoint->x) / 50.0;
	velY2 = (this->secondTarget.y - secondPoint->y) / 50.0;
}

bool NURBS::OnRightMouseClicked(sf::Vector2i position)
{
	auto newPoint = new NURBPoint(position.x, position.y);

	this->points.push_back(newPoint);

	this->lastCreatedPoint = newPoint;

	return true;
}

bool NURBS::OnLeftMouseClicked(sf::Vector2i position)
{
	if (selectedEntity != NULL) {
		selectedEntity->selected = false;
	}

	selectedEntity = this->EntityInMousePosition(position.x, position.y);

	if (selectedEntity != NULL) {
		selectedEntity->selected = true;
		return true;
	}
	return false;
}

bool NURBS::OnRightMouseReleased(sf::Vector2i position)
{
	return false;
}

bool NURBS::OnLeftMouseReleased(sf::Vector2i position)
{
	if (selectedEntity != NULL) {
		selectedEntity->selected = false;
		selectedEntity = NULL;
	}
	return false;
}

bool NURBS::OnRightMouseDragged(sf::Vector2i position)
{
	return false;
}

bool NURBS::OnLeftMouseDragged(sf::Vector2i position)
{
	if (selectedEntity != NULL) {
		selectedEntity->MoveTo(position.x, position.y);
		return true;
	}
	return false;
}

Entity* NURBS::EntityInMousePosition(int x, int y)
{
	for (auto point : points) {
		if (point->IsInside(x, y)) {
			return point;
		}
	}

	return NULL;
}

void NURBS::ToggleHidePoints()
{
	this->hidePoints = !this->hidePoints;
}

bool NURBS::IsReady()
{
	return this->points.size() >= 3;
}

void NURBS::Update() {
	lines.clear();

	if (this->IsReady()) {
		last = sf::Vector2i(points.at(0)->x, points.at(0)->y);

		for (double i = 0; i < 1; i += 0.001) {
			sf::Vector2i point;

			this->Interpolate(i, &point);

			lines.push_back(sf::Vertex(sf::Vector2f(last.x, last.y)));
			lines.push_back(sf::Vertex(sf::Vector2f(point.x, point.y)));

			last = point;
		}
		
		if (target != NULL) {
			auto firstPoint = this->points.at(0);
			auto secondPoint = this->points.at(1);
			
			if (firstPoint->Distance(this->target->x, this->target->y) > 10)
				firstPoint->Move(velX, velY);
			else {
				firstPoint->MoveTo(this->target->x, this->target->y);
			}

			if (secondPoint->Distance(this->secondTarget.x, this->secondTarget.y) > 10)
				secondPoint->Move(velX2, velY2);
			else {
				secondPoint->MoveTo(this->secondTarget.x, this->secondTarget.y);
			}
		}
	}
}

int binomialCoeff(int n, int k)
{
	// Base Cases  
	if (k == 0 || k == n)
		return 1;

	// Recur  
	return binomialCoeff(n - 1, k - 1) +
		binomialCoeff(n - 1, k);
}

void NURBS::Interpolate(double time, sf::Vector2i* result)
{
	auto controlPoints = this->points;
	int n = controlPoints.size() - 1;

	result->x = 0, result->y = 0;

	for (size_t i = 0; i < controlPoints.size(); ++i) {
		auto binomial = binomialCoeff(n, i);

		double it = (1.0 - time);

		result->x += (
			pow(it, n - i) * pow(time, i) * controlPoints[i]->x * binomial
			);

		result->y += (
			pow(it, n - i) * pow(time, i) * controlPoints[i]->y * binomial
			);
	}
}

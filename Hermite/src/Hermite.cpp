#include "../include/Hermite.h"

Hermite::Hermite()
{
	auto firstPoint = new Point(500, 500);

	firstPoint->showPrimaryTangent = false;
	firstPoint->showSecondaryTangent = false;

	lastCreatedPoint = firstPoint;

	points.push_back(firstPoint);
}


Hermite::~Hermite()
{
}

void Hermite::Draw() {
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

bool Hermite::OnRightMouseClicked(sf::Vector2i position)
{
	auto newPoint = new Point(position.x, position.y);

	this->points.push_back(newPoint);

	this->lastCreatedPoint->showPrimaryTangent = true;

	this->lastCreatedPoint = newPoint;

	if (this->tangentForEach) {
		this->lastCreatedPoint->showSecondaryTangent = true;
		this->lastCreatedPoint->showPrimaryTangent = false;
	}

	return true;
}

bool Hermite::OnLeftMouseClicked(sf::Vector2i position)
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

bool Hermite::OnRightMouseReleased(sf::Vector2i position)
{
	return false;
}

bool Hermite::OnLeftMouseReleased(sf::Vector2i position)
{
	if (selectedEntity != NULL) {
		selectedEntity->selected = false;
		selectedEntity = NULL;
	}
	return false;
}

bool Hermite::OnRightMouseDragged(sf::Vector2i position)
{
	return false;
}

bool Hermite::OnLeftMouseDragged(sf::Vector2i position)
{
	if (selectedEntity != NULL) {
		selectedEntity->MoveTo(position.x, position.y);
		return true;
	}
	return false;
}

Entity* Hermite::EntityInMousePosition(int x, int y)
{
	for (auto point : points) {
		if (point->IsInside(x, y)) {
			return point;
		}
		if (point->ptrTangent->IsInside(x, y)) {
			return point->ptrTangent;
		}
		if (point->ptrTangentSecondary->IsInside(x, y) && tangentForEach) {
			return point->ptrTangentSecondary;
		}
	}

	return NULL;
}

Point* Hermite::FirstPoint()
{
	return this->points.at(0);
}

void Hermite::ToggleHidePoints()
{
	this->hidePoints = !this->hidePoints;
}

bool Hermite::IsReady()
{
	return this->points.size() > 1;
}

void Hermite::Update() {
	lines.clear();
	if (this->IsReady()) {
		last = sf::Vector2i(points.at(0)->x, points.at(0)->y);

		if (tangentForEach) {
			for (int pair = 0; pair < points.size() - 1; pair++) {
				for (double i = 0; i < 1; i += 0.01) {
					auto pointA = points.at(pair);
					auto pointB = points.at(pair + 1);

					this->PairInterpolate(i, pointA, pointB, pointA->NormalizedTangent(), pointB->NormalizedTangentSecondary(), &point);

					last = point;

					lines.push_back(sf::Vertex(sf::Vector2f(last.x, last.y)));
					lines.push_back(sf::Vertex(sf::Vector2f(point.x, point.y)));
				}
			}
		}
		else {
			for (double i = 0; i < 1; i += 0.0001) {
				this->Interpolate(i, &point);

				//sf::Vertex line[] =
				//{
				//	sf::Vertex(sf::Vector2f(last.x, last.y)),
				//	sf::Vertex(sf::Vector2f(point.x, point.y))
				//};

				last = point;
				lines.push_back(sf::Vertex(sf::Vector2f(last.x, last.y)));
				lines.push_back(sf::Vertex(sf::Vector2f(point.x, point.y)));
			}
		}
	}
}

void Hermite::Interpolate(double time, sf::Vector2i* result)
{
	int n = points.size();
	int dimensions = 2;

	time = time * (n - 1);
	double i0 = (int) time | 0;
	double i1 = i0 + 1;

	if (i0 > n - 1) {
		perror("Out of bound!\n");
		exit(1);
	}

	if (i0 == n - 1) {
		i1 = i0;
	}

	double scale = i1 - i0;

	time = (time - i0) / scale;

	double t2 = time * time;
	double it = 1 - time;
	double it2 = it * it;
	double tt = 2 * time;

	double h00 = (1 + tt) * it2;
	double h10 = time * it2;
	double h01 = t2 * (3 - tt);
	double h11 = t2 * (time - 1);

	Point* firstPoint = points.at(i0);
	Point* secondPoint = points.at(i1);

	result->x = h00 * firstPoint->x +
		h10 * firstPoint->NormalizedTangent().x * scale +
		h01 * secondPoint->x +
		h11 * secondPoint->NormalizedTangent().x * scale;

	result->y = h00 * firstPoint->y +
		h10 * firstPoint->NormalizedTangent().y * scale +
		h01 * secondPoint->y +
		h11 * secondPoint->NormalizedTangent().y * scale;
}

void Hermite::PairInterpolate(double time, Point* pointA, Point* pointB, sf::Vector2i tanA, sf::Vector2i tanB, sf::Vector2i* result)
{
	int n = 2;
	int dimensions = 2;

	time = time * (n - 1.0);
	double i0 = (int) time | 0;
	double i1 = i0 + 1.0;

	if (i0 > n - 1.0) {
		perror("Out of bound!\n");
		exit(1);
	}

	if (i0 == n - 1.0) {
		i1 = i0;
	}

	double scale = i1 - i0;

	time = (time - i0) / scale;

	double t2 = time * time;
	double it = 1.0 - time;
	double it2 = it * it;
	double tt = 2.0 * time;

	double h00 = (1.0 + tt) * it2;
	double h10 = time * it2;
	double h01 = t2 * (3.0 - tt);
	double h11 = t2 * (time - 1);

	result->x = h00 * pointA->x +
		h10 * tanA.x * scale +
		h01 * pointB->x +
		h11 * tanB.x * scale;

	result->y = h00 * pointA->y +
		h10 * tanA.y * scale +
		h01 * pointB->y +
		h11 * tanB.y * scale;
}

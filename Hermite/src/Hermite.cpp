#include "../include/Hermite.h"



Hermite::Hermite()
{
}


Hermite::~Hermite()
{
}

void Hermite::Interpolate(double time, std::vector<Point*> points, sf::Vector2i* result)
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

	result->x = h00 * pointA->x +
		h10 * tanA.x * scale +
		h01 * pointB->x +
		h11 * tanB.x * scale;

	result->y = h00 * pointA->y +
		h10 * tanA.y * scale +
		h01 * pointB->y +
		h11 * tanB.y * scale;
}

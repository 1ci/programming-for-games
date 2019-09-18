#ifndef GRID_H
#define GRID_H

#include "vec2.h"
#include <vector>

class Shape;

struct Grid
{
	static const vec2 DEFAULT_MINS;
	static const vec2 DEFAULT_MAXS;

	Grid();
	Grid(const vec2& mins, const vec2& maxs);
	~Grid();

	void AddShape(Shape* shape);
	void MoveShapes();
	unsigned int DeleteCollidingShapes();
	vec2 GetRandomGridPosition() const;
	void PlaceCircles(unsigned int numOfCircles, float lowRadius, float highRadius);
	void PlaceSquares(unsigned int numOfSquares, float lowSide, float highSide);

	const vec2 m_vecGridMins;
	const vec2 m_vecGridMaxs;

	std::vector<Shape*> m_shapes;
};

#endif // GRID_H

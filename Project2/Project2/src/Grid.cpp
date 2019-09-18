#include "Grid.h"
#include <iostream>
#include "Shape.h"
#include "Square.h"
#include "Circle.h"
#include "Util.h"
#include "Debug.h"

const vec2 Grid::DEFAULT_MINS(-500, -500);
const vec2 Grid::DEFAULT_MAXS(500, 500);

Grid::Grid()
	: m_vecGridMins(DEFAULT_MINS)
	, m_vecGridMaxs(DEFAULT_MAXS)
{
	std::cout << "Making a grid with mins(" << m_vecGridMins.ToString()
		<< ") and maxs(" << m_vecGridMaxs.ToString() << ")" << std::endl;
}

Grid::Grid(const vec2& mins, const vec2& maxs)
	: m_vecGridMins(mins)
	, m_vecGridMaxs(maxs)
{
	std::cout << "Making a grid with mins(" << m_vecGridMins.ToString()
		<< ") and maxs(" << m_vecGridMaxs.ToString() << ")" << std::endl;
}

Grid::~Grid()
{
	for (std::vector<Shape*>::size_type i = 0; i < m_shapes.size(); i++)
	{
		delete m_shapes[i];
	}
}

void Grid::AddShape(Shape* shape)
{
	m_shapes.push_back(shape);
	shape->ClampToGrid(*this);
	std::cout << "Adding " << shape->ToString() << std::endl;
}

void Grid::MoveShapes()
{
	for (std::vector<Shape*>::size_type i = 0; i < m_shapes.size(); i++)
	{
		/* Calculate a random velocity amount */
		float x = getRandFloat(m_vecGridMins.x / 50, m_vecGridMaxs.x / 50);
		float y = getRandFloat(m_vecGridMins.y / 50, m_vecGridMaxs.y / 50);

		/* Move the shape */
		vec2 velocity(x, y);
		m_shapes[i]->Move(velocity);

		/* Clamp to grid bounds */
		m_shapes[i]->ClampToGrid(*this);
	}
}

unsigned int Grid::DeleteCollidingShapes()
{
	unsigned int numOfCollidingShapes = 0;

	/* Iterate over the array of shapes */
	for (std::vector<Shape*>::size_type i = 0; i < m_shapes.size() - 1; i++)
	{
		/* For every shape, check for collisions against other shapes */
		for (std::vector<Shape*>::size_type j = i + 1; j < m_shapes.size(); j++)
		{
			if (m_shapes[i]->Collides(*m_shapes[j]))
			{
#ifdef COLLISION_DEBUG_GRID
				std::cout << "Collision of ";
				std::cout << m_shapes[i]->GetShapeName() << " #";
				std::cout << m_shapes[i]->GetId() << " and ";
				std::cout << m_shapes[j]->GetShapeName() << " #";
				std::cout << m_shapes[j]->GetId() << " detected." << std::endl;
#endif
				/* Remove the objects */
				delete m_shapes[j];
				delete m_shapes[i];
				m_shapes[j] = nullptr;
				m_shapes[i] = nullptr;
				m_shapes.erase(m_shapes.begin() + j);
				m_shapes.erase(m_shapes.begin() + i);

				j = i + 1;
				numOfCollidingShapes += 2;

				if (m_shapes.size() == 0)
					return numOfCollidingShapes;
			}
		}
	}
	return numOfCollidingShapes;
}

vec2 Grid::GetRandomGridPosition() const
{
	float x = getRandFloat(m_vecGridMins.x, m_vecGridMaxs.x);
	float y = getRandFloat(m_vecGridMins.y, m_vecGridMaxs.y);

	return vec2(x, y);
}

void Grid::PlaceCircles(unsigned int numOfCircles, float lowRadius, float highRadius)
{
	for (unsigned int i = 0; i < numOfCircles; ++i)
	{
		/* Calculate a random position and radius */
		vec2 position = GetRandomGridPosition();
		float radius = getRandFloat(lowRadius, highRadius);

		AddShape(new Circle(position, radius));
	}
}

void Grid::PlaceSquares(unsigned int numOfSquares, float lowSide, float highSide)
{
	for (unsigned int i = 0; i < numOfSquares; ++i)
	{
		/* Calculate a random position and side */
		vec2 position = GetRandomGridPosition();
		float side = getRandFloat(lowSide, highSide);

		AddShape(new Square(position, side));
	}
}

#include "Circle.h"
#include "Collision.h"
#include <iostream>
#include <sstream>
#include "Square.h"
#include "Grid.h"
#include <iomanip>
#include <cmath>

const std::string Circle::m_sName("Circle");
unsigned int Circle::m_idCounter = 0;

Circle::Circle()
	: m_fRadius(1.0f)
	, m_id(m_idCounter++)
{
}

Circle::Circle(float radius)
	: m_fRadius(std::fabsf(radius))
	, m_id(m_idCounter++)
{
}

Circle::Circle(const vec2& position)
	: Shape(position)
	, m_fRadius(1.0f)
	, m_id(m_idCounter++)
{
}

Circle::Circle(const vec2& position, float radius)
	: Shape(position)
	, m_fRadius(std::fabsf(radius))
	, m_id(m_idCounter++)
{
}

Circle::Circle(const Circle& other)
	: Shape(other.m_vecPosition)
	, m_fRadius(other.m_fRadius)
	, m_id(m_idCounter++)
{
}

Circle::~Circle()
{
	std::cout << "Deleting " << ToString() << std::endl;
}

Circle& Circle::operator=(const Circle& other)
{
	if (this == &other)
	{
		return *this;
	}

	m_vecPosition = other.m_vecPosition;
	m_fRadius = other.m_fRadius;

	return *this;
}

bool Circle::operator==(const Circle& other) const
{
	if (this == &other)
	{
		return true;
	}

	return (m_vecPosition == other.m_vecPosition && 
			m_fRadius == other.m_fRadius);
}

float Circle::GetRadius() const
{
	return m_fRadius;
}

void Circle::SetRadius(float radius)
{
	m_fRadius = std::fabsf(radius);
}

bool Circle::Collides(const Circle& circle) const
{
	return Collide(*this, circle);
}

bool Circle::Collides(const Square& square) const
{
	return Collide(*this, square);
}

bool Circle::Collides(Shape& other) const
{
	/* I know... I'm sorry. */
	Circle* c = dynamic_cast<Circle*>(&other);
	if (c != nullptr)
	{
		return Collide(*this, *c);
	}

	Square* s = dynamic_cast<Square*>(&other);
	if (s != nullptr)
	{
		return Collide(*this, *s);
	}

	return false;
}

void Circle::ClampToGrid(const Grid& grid)
{
	// Clamp to grid bounds
	if (m_vecPosition.x - m_fRadius < grid.m_vecGridMins.x)
	{
		m_vecPosition.x = grid.m_vecGridMins.x + m_fRadius;
	}
	if (m_vecPosition.x + m_fRadius > grid.m_vecGridMaxs.x)
	{
		m_vecPosition.x = grid.m_vecGridMaxs.x - m_fRadius;
	}
	if (m_vecPosition.y - m_fRadius < grid.m_vecGridMins.y)
	{
		m_vecPosition.y = grid.m_vecGridMins.y + m_fRadius;
	}
	if (m_vecPosition.y + m_fRadius > grid.m_vecGridMaxs.x)
	{
		m_vecPosition.y = grid.m_vecGridMaxs.y - m_fRadius;
	}
}

unsigned int Circle::GetId() const
{
	return m_id;
}

const std::string& Circle::GetShapeName() const
{
	return m_sName;
}

std::string Circle::GetShapeInfo() const
{
	std::ostringstream stream;
	stream << "Radius: " << std::fixed << std::setprecision(1) << m_fRadius;
	return stream.str();
}

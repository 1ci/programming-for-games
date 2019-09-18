#include "Square.h"
#include "Collision.h"
#include <iostream>
#include <sstream>
#include "Circle.h"
#include "Grid.h"
#include <iomanip>
#include <cmath>

const std::string Square::m_sName("Square");
unsigned int Square::m_idCounter = 0;

Square::Square()
	: m_fSide(1.0f)
	, m_id(m_idCounter++)
{
}

Square::Square(float side)
	: m_fSide(std::fabsf(side))
	, m_id(m_idCounter++)
{
}

Square::Square(const vec2& position)
	: Shape(position)
	, m_fSide(1.0f)
	, m_id(m_idCounter++)
{
}

Square::Square(const vec2& position, float side)
	: Shape(position)
	, m_fSide(std::fabsf(side))
	, m_id(m_idCounter++)
{
}

Square::Square(const Square& other)
	: Shape(other.m_vecPosition)
	, m_fSide(other.m_fSide)
	, m_id(m_idCounter++)
{
}

Square::~Square()
{
	std::cout << "Deleting " << ToString() << std::endl;
}

Square& Square::operator=(const Square& other)
{
	if (this == &other)
	{
		return *this;
	}

	m_vecPosition = other.m_vecPosition;
	m_fSide = other.m_fSide;

	return *this;
}

bool Square::operator==(const Square& other) const
{
	if (this == &other)
	{
		return true;
	}

	return (m_vecPosition == other.m_vecPosition &&
		m_fSide == other.m_fSide);
}

float Square::GetSide() const
{
	return m_fSide;
}

void Square::SetSide(float side)
{
	m_fSide = std::fabsf(side);
}

bool Square::Collides(const Circle& circle) const
{
	return Collide(*this, circle);
}

bool Square::Collides(const Square& square) const
{
	return Collide(*this, square);
}

bool Square::Collides(Shape& other) const
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

void Square::ClampToGrid(const Grid& grid)
{
	// Clamp to grid bounds
	if (m_vecPosition.x - m_fSide < grid.m_vecGridMins.x)
	{
		m_vecPosition.x = grid.m_vecGridMins.x + m_fSide;
	}
	if (m_vecPosition.x + m_fSide > grid.m_vecGridMaxs.x)
	{
		m_vecPosition.x = grid.m_vecGridMaxs.x - m_fSide;
	}
	if (m_vecPosition.y - m_fSide < grid.m_vecGridMins.y)
	{
		m_vecPosition.y = grid.m_vecGridMins.y + m_fSide;
	}
	if (m_vecPosition.y + m_fSide > grid.m_vecGridMaxs.x)
	{
		m_vecPosition.y = grid.m_vecGridMaxs.y - m_fSide;
	}
}

unsigned int Square::GetId() const
{
	return m_id;
}

const std::string& Square::GetShapeName() const
{
	return m_sName;
}

std::string Square::GetShapeInfo() const
{
	std::ostringstream stream;
	stream << "Side: " << std::fixed << std::setprecision(1) << m_fSide;
	return stream.str();
}

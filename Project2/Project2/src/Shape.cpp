#include "Shape.h"
#include "vec2.h"
#include <iostream>
#include <sstream>
#include "Debug.h"

Shape::Shape()
{
}

Shape::Shape(const vec2& position)
	: m_vecPosition(position)
{
}

Shape::Shape(const Shape& other)
	: m_vecPosition(other.m_vecPosition)
{
}

Shape::~Shape()
{
}

vec2 Shape::GetPosition() const
{
	return m_vecPosition;
}

void Shape::SetPosition(const vec2& position)
{
	m_vecPosition = position;
}

void Shape::Move(const vec2& velocity)
{
	m_vecPosition += velocity;

#ifdef MOVE_DEBUG
	std::cout << "Move " << GetShapeName();
	std::cout << " #" << GetId() << " ";
	std::cout << "with vel: " << velocity.ToString() << ", ";
	std::cout << "pos: " << m_vecPosition.ToString() << std::endl;
#endif
}

std::string Shape::ToString() const
{
	std::ostringstream stream;

	stream << GetShapeName() << " ";
	stream << "#" << GetId() << ", ";
	stream << GetShapeInfo() << ", ";
	stream << "Position: " << m_vecPosition.ToString();

	return stream.str();
}

std::ostream& operator<<(std::ostream& stream, const Shape& shape)
{
	return stream << shape.ToString();
}

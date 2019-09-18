#include "vec2.h"
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

vec2::vec2()
	: x(0.0f), y(0.0f)
{
}

vec2::vec2(float x, float y)
	: x(x), y(y)
{
}

vec2::vec2(const vec2& other)
	: x(other.x), y(other.y)
{
}

bool vec2::operator==(const vec2& other) const
{
	if (this == &other)
	{
		return true;
	}

	// floating point inaccuracy. TODO: use epsilon?
	return (x == other.x && y == other.y);
}

vec2& vec2::operator=(const vec2& other)
{
	if (this == &other)
	{
		return *this;
	}

	x = other.x;
	y = other.y;

	return *this;
}

vec2 vec2::operator+(const vec2& other) const
{
	return vec2(x + other.x, y + other.y);
}

vec2 vec2::operator-(const vec2& other) const
{
	return vec2(x - other.x, y - other.y);
}

vec2 vec2::operator*(const vec2& other) const
{
	return vec2(x * other.x, y * other.y);
}

vec2 vec2::operator/(const vec2& other) const
{
	return vec2(x / other.x, y / other.y);
}

vec2& vec2::operator+=(const vec2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

vec2& vec2::operator-=(const vec2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

float vec2::Length() const
{
	return std::sqrtf(x * x + y * y);
}

float vec2::Distance(const vec2& other) const
{
	return std::fabsf( Length() - other.Length() );
}

std::string vec2::ToString() const
{
	std::ostringstream stream;

	stream << "x: " << std::fixed << std::setprecision(1) << x << ", ";
	stream << "y: " << std::fixed << std::setprecision(1) << y;

	return stream.str();
}

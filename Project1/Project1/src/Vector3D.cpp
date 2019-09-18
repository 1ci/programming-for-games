#include "Vector3D.h"
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

Vector3D::Vector3D()
	: x(0.0f), y(0.0f), z(0.0f)
{
	//std::cout << "Calling Vector3D() Constructor" << std::endl;
}

Vector3D::Vector3D(float x, float y, float z)
	: x(x), y(y), z(z)
{
	//std::cout << "Calling Vector3D(x,y,z) Constructor" << std::endl;
}

Vector3D::Vector3D(const Vector3D& other)
	: x(other.x), y(other.y), z(other.z)
{
	//std::cout << "Calling Vector3D Copy Constructor" << std::endl;
}

Vector3D::Vector3D(Vector3D&& other)
	: x(other.x), y(other.y), z(other.z)
{
	//std::cout << "Calling Vector3D Move Constructor" << std::endl;
}

Vector3D& Vector3D::operator=(const Vector3D& other)
{
	//std::cout << "Calling Vector3D Copy Assignment" << std::endl;

	if (this == &other)
		return *this;

	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Vector3D& Vector3D::operator=(Vector3D&& other)
{
	//std::cout << "Calling Vector3D Move Assignment" << std::endl;

	if (this == &other)
		return *this;

	x = other.x;
	y = other.y;
	z = other.z;

	return *this;
}

Vector3D& Vector3D::Add(const Vector3D& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3D& Vector3D::Subtract(const Vector3D& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3D& Vector3D::Multiply(float value)
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

Vector3D& Vector3D::Divide(float value)
{
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

Vector3D operator+(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(
		left.x + right.x,
		left.y + right.y,
		left.z + right.z);
}

Vector3D operator-(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(
		left.x - right.x,
		left.y - right.y,
		left.z - right.z);
}

Vector3D operator*(const Vector3D& left, float value)
{
	return Vector3D(
		left.x * value,
		left.y * value,
		left.z * value);
}

Vector3D operator*(float value, const Vector3D& right)
{
	return operator*(right, value);
}

Vector3D operator/(const Vector3D& left, float value)
{
	return Vector3D(
		left.x / value,
		left.y / value,
		left.z / value);
}

Vector3D operator/(float value, const Vector3D& right)
{
	return operator/(right, value);
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
	return Add(other);
}

Vector3D& Vector3D::operator-=(const Vector3D& other)
{
	return Subtract(other);
}

Vector3D& Vector3D::operator*=(float value)
{
	return Multiply(value);
}

Vector3D& Vector3D::operator/=(float value)
{
	return Divide(value);
}

float Vector3D::Magnitude() const
{
	return std::sqrtf(x * x + y * y + z * z);
}

Vector3D Vector3D::Normalise() const
{
	float length = Magnitude();
	return Vector3D(x / length, y / length, z / length);
}

float Vector3D::Dot(const Vector3D& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float Vector3D::operator*(const Vector3D& other) const
{
	return Dot(other);
}

Vector3D Vector3D::Cross(const Vector3D& other)
{
	return Vector3D(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

Vector3D operator%(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(
		left.y * right.z - left.z * right.y,
		left.z * right.x - left.x * right.z,
		left.x * right.y - left.y * right.x);
}

Vector3D Vector3D::UnitOrthogonal(const Vector3D& first, const Vector3D& second)
{
	return (first % second).Normalise();
}

std::string Vector3D::ToString() const
{
	std::stringstream result;
	result << "Vector3D: (" << x << ", " << y << ", " << z << ")";
	return result.str();
}

std::ostream& operator<<(std::ostream& stream, const Vector3D& vec)
{
	stream << vec.ToString();
	return stream;
}

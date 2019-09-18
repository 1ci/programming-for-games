#pragma once

#include <iostream>
#include <string>

struct Vector3D
{
	float x, y, z;

	Vector3D();
	Vector3D(float x, float y, float z);

	// Copy constructor
	Vector3D(const Vector3D& other);

	// Move constructor
	Vector3D(Vector3D&& other);

	// Copy assignment
	Vector3D& operator=(const Vector3D& other);

	// Move assignment
	Vector3D& operator=(Vector3D&& other);

	// Operations
	Vector3D& Add(const Vector3D& other);
	Vector3D& Subtract(const Vector3D& other);
	Vector3D& Multiply(float value);
	Vector3D& Divide(float value);

	friend Vector3D operator+(const Vector3D& left, const Vector3D& right);
	friend Vector3D operator-(const Vector3D& left, const Vector3D& right);
	friend Vector3D operator*(const Vector3D& left, float value);
	friend Vector3D operator/(const Vector3D& left, float value);

	friend Vector3D operator*(float value, const Vector3D& right);
	friend Vector3D operator/(float value, const Vector3D& right);

	Vector3D& operator+=(const Vector3D& other);
	Vector3D& operator-=(const Vector3D& other);
	Vector3D& operator*=(float value);
	Vector3D& operator/=(float value);

	float Magnitude() const;
	Vector3D Normalise() const;

	// Dot (scalar) product
	float Dot(const Vector3D& other) const;
	float operator*(const Vector3D& other) const;

	// Cross (vector) product
	Vector3D Cross(const Vector3D& other);
	friend Vector3D operator%(const Vector3D& left, const Vector3D& right);

	// Returns a unit vector orthogonal to two given vectors
	Vector3D UnitOrthogonal(const Vector3D& first, const Vector3D& second);

	// For output
	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& stream, const Vector3D& vec);
};

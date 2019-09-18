#ifndef VEC2_H
#define VEC2_H

#include <string>

struct vec2
{
	float x, y;

	vec2();
	vec2(float x, float y);
	vec2(const vec2& other);

	bool operator==(const vec2& other) const;
	vec2& operator=(const vec2& other);

	vec2 operator+(const vec2& other) const;
	vec2 operator-(const vec2& other) const;
	vec2 operator*(const vec2& other) const;
	vec2 operator/(const vec2& other) const;

	vec2& operator+=(const vec2& other);
	vec2& operator-=(const vec2& other);

	float Length() const;
	float Distance(const vec2& other) const;

	std::string ToString() const;
};

#endif // VEC2_H

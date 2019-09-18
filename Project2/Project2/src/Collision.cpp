#include "Collision.h"
#include <cmath>
#include "vec2.h"
#include "Circle.h"
#include "Square.h"
#include <iostream>
#include "Debug.h"
#include <iomanip>

float clampf(float value, float min, float max);

bool Collide(const Circle& first, const Circle& second)
{
	// Calculate distance between center points of circles
	float distance = first.GetPosition().Distance(second.GetPosition());

#ifdef COLLISION_DEBUG_CIRCLES
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "Dist between circles #" << first.GetId();
	std::cout << " & #" << second.GetId() << ": ";
	std::cout << distance << " ";
	std::cout << "Radii Sum: " << (first.GetRadius() + second.GetRadius()) << std::endl;
#endif

	// If it's lower than the sum of radii, then they intersect
	return distance < first.GetRadius() + second.GetRadius();
}

bool Collide(const Square& first, const Square& second)
{
	// Calculate distance beteen the center of squares for each axis
	vec2 distance;
	distance.x = std::fabsf( first.GetPosition().x - second.GetPosition().x );
	distance.y = std::fabsf( first.GetPosition().y - second.GetPosition().y );

	// They overlap if both distances are lower than the sum of half their sides
	float sideDistance = first.GetSide() / 2 + second.GetSide() / 2;

#ifdef COLLISION_DEBUG_SQUARES
	std::cout << std::fixed << std::setprecision(1);
	std::cout << "Dist between squares #" << first.GetId();
	std::cout << " & #" << second.GetId() << ": ";
	std::cout << distance.ToString() << " ";
	std::cout << "Side Dist: " << sideDistance << std::endl;
#endif

	return distance.x < sideDistance && distance.y < sideDistance;
}

bool Collide(const Circle& circle, const Square& square)
{
	// Find the closest edge around the square relative to circle's center
	vec2 edge;
	edge.x = clampf(circle.GetPosition().x, 
		square.GetPosition().x - square.GetSide(), 
		square.GetPosition().x + square.GetSide());

	edge.y = clampf(circle.GetPosition().y,
		square.GetPosition().y - square.GetSide(),
		square.GetPosition().y + square.GetSide());

	// Calculate distance between edge and center of circle
	float distance = edge.Distance(circle.GetPosition());

#ifdef COLLISION_DEBUG_CIRCLES_AND_SQUARES
	std::cout << std::fixed << std::setprecision(1);
	//std::cout << "Edge Loc: " << edge.ToString() << " ";
	std::cout << "Dist between square #" << square.GetId();
	std::cout << " & circle #" << circle.GetId() << ": " << distance << " ";
	std::cout << "Radius: " << circle.GetRadius() << std::endl;
#endif

	// If it's lower than circle's radius, then they intersect
	return distance < circle.GetRadius();
}

bool Collide(const Square& square, const Circle& circle)
{
	return Collide(circle, square);
}

float clampf(float value, float min, float max)
{
	// MIN(MAX(value, MIN(min, max)), MAX(min, max))
	return std::fminf( std::fmaxf(value, std::fminf(min, max)), std::fmaxf(min, max) );
}

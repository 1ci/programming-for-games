#include <iostream>
#include <ctime>
#include "Grid.h"

/* Check out Debug.h if you want to view/hide debug messages. */
int main(int argc, char** argv)
{
	/* initialize random seed: */
	srand(static_cast <unsigned int> (time(0)));

	/* Create a 2D grid. You can supply custom mins/maxs */
	/* but I suggest you keep it default for simplicity ^_^ */
	Grid g;

	/* Place circles/squares on the grid. */
	/* Shape positions are randomly calculated and */
	/* clamped within the dimensions of the grid. */
	/* Random radius and side bounds are supplied as params. */
	g.PlaceCircles(2, 10, 50); // experiment with these
	g.PlaceSquares(0, 10, 50); // experiment with these
	
	std::cout << "Number of shapes on grid: " << g.m_shapes.size() << std::endl;

	/* While there is more than one shape on the grid.. */
	while (g.m_shapes.size() > 1)
	{
		/* Move each shape by a random velocity amount. */
		/* I have decided to keep the randomized vel amount */
		/* relative to the dimensions of the grid. */
		/* You can look at the implementation and change it as you like tho. */
		g.MoveShapes();

		/* Check for collisions and delete colliding shapes. */
		/* This function returns the number of colliding shapes it's removed. */
		if (g.DeleteCollidingShapes() > 0)
		{
			/* Let's give a description of how many shapes are left on the grid. */
			std::cout << "Number of shapes on grid: " << g.m_shapes.size() << std::endl;
		}
	}
	/* The program will get here if only one shape has remained on the grid */
	/* or if all shapes have collided and therefore been removed. */

	std::cin.get();
	return 0;
}

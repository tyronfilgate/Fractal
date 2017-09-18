#pragma once

#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gl/glut.h>
#include "coords.h"
#include "RGB.h"

/**
* @class fractalGenerator
* @brief A class which contains methods for procedurally generating fractals.
*
* @author Morgan Smolder
* @version 01
* @date 15/09/2017
*/

class fractalGenerator
{
public:
	fractalGenerator();

	/**
	* @brief Draws fractals within a given gridsize and scale.
	*
	* @param gridsize - The size of the grids borders.
	* @param scale - The scale at which to draw the fractals.
	*/
	void drawFractals(int gridsize, int scale);

	/**
	* @brief Renders the fractals
	*
	* @param c1 - RGB value specifing the fractal tip color
	* @param c2 - RGB value specifing the mid fractal color
	* @param c3 - RGB value specifying the end fractal color
	* @pre The fractals have already been drawn.
	*/
	void renderFractals(RGB c1, RGB c2, RGB c3);

private:
	///The verticies of the fractals.
	std::vector<point3> vertices;
	///The indicies of the verticies of the fractals.
	std::vector<int> indices;

	/**
	* @brief Generates fractals according to the diamond-square algorithim.
	*
	* @param size - The size of the grid to be used when generating the fractals.
	* @param lowerrange - The lower range of the random values to be added to each point in the grid.
	* @param upperrange - The upper range of the random values to be added to each point in the grid.
	* @param coords - The coordinates of the grid.
	* @param coordsstart - The point in the grid to start at.
	*/
	void genDiamondSquare(int size, int lowerrange, int upperrange, std::vector<point3> & coords, unsigned coordsstart);

	/**
	* @brief Creates the vertices for a 2d triangle strip plane.
	*
	* @param min1 - The starting x value.
	* @param max1 - The starting z value.
	* @param min2 - The ending x value.
	* @param max2 - The ending z value.
	* @param coords - A vector to store the new vertices in.
	* @param scale - The scale at which to draw the vertices.
	*/
	void genPlaneVertices(int min1, int max1, int min2, int max2, std::vector<point3> & coords, int scale);

	/**
	* @brief Creates the vertex indices for a 2d triangle strip plane along the XZ axis.
	*
	* @param min1 - The starting x value.
	* @param max1 - The starting z value.
	* @param indices - A vector to store the new vertex indicies in.
	*/
	void genPlaneIndices(int min, int max, std::vector<int> & indices);

	/**
	* @brief Returns a random float in a given range.
	*
	* @param floor - The minimum allowable random value.
	* @param ceiling - The maximum allowable random value.
	* @return float - The randomly generated float.
	*/
	float genRand(int floor, int ceiling);
};


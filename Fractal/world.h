#pragma once
#include "fractalGenerator.h"
#include "city.h"

/**
* @class world
* @brief A class which contains methods for procedurally generating the world 
*		  used in fractal.
*
* @author Morgan Smolder
* @version 01
* @date 15/09/2017
*/

class world
{
public:
	/**
	* @brief Generates a world of given size and scale.
	*
	* @param size - The size of the worlds borders.
	* @param scale - The scale at which to draw the world.
	*/
	void genWorld(int size, int scale);

	/**
	* @brief Creates a display list containing all the world geometry.
	*
	* @param listno - An integer to bind the display list to.
	* @pre The world has already been drawn.
	*/
	void createDisplayList(const int & listno);

	/**
	* @brief Returns a valid start point for the player.
	*
	* @return point3 - The starting coordinates at which to place the player.
	* @pre The city has already been drawn.
	*/
	const point3& getStartCoord() const;

	/**
	* @brief Returns The bounding box information for all objects in the world.
	*
	* @return std::vector<BBoxCoords> - A vector containing the bounding box information for the city.
	* @pre The world has already been drawn.
	*/
	const std::vector<BBoxCoords> & getBounds();

private:
	///Object used to generate the fractals seen in the cities sky.
	fractalGenerator f;
	///Object used to generate the city.
	city c;
	///The worlds three tone color pallet is contained in these structs.
	RGB c1, c2, c3;
	///Contains bounding box info for the world.
	std::vector<BBoxCoords> bounds;
	///Contains the vertices used to draw the planes at the edges of the world.
	std::vector<point3> vertices;
	///Contains the indices of the vertices used to draw the planes at the edges of the world.
	std::vector<int> indices;

	/**
	* @brief Creates the vertices for a 2d triangle strip plane along the XZ axis.
	*
	* @param min1 - The starting x value.
	* @param max1 - The starting z value.
	* @param min2 - The ending x value.
	* @param max2 - The ending z value.
	* @param coords - A vector to store the new vertices in.
	* @param scale - The scale at which to draw the vertices.
	*/
	void genPlaneVerticesXZ(int min1, int max1, int min2, int max2, std::vector<point3> & coords, int scale);

	/**
	* @brief Creates the vertex indices for a 2d triangle strip plane along the XZ axis.
	*
	* @param min1 - The starting x value.
	* @param max1 - The starting z value.
	* @param indices - A vector to store the new vertex indicies in.
	*/
	void genPlaneIndices(int min, int max, std::vector<int> & indices);

	/**
	* @brief Draws a triangle strip plane with given vertices and indices.
	*
	* @param indices - The vertices to draw
	* @param vertices - The indices of the verticies to draw.
	* @param c3 - The color to draw the plane.
	*/
	void drawPlain(std::vector<point3> & vertices, std::vector<int> & indices, RGB c3);

	/**
	* @brief Wrapper for generating the vertices, indices and plains in the world.
	*
	* @param gridsize - The size of the worlds borders.
	* @param scale - The scale at which to draw the world.
	*/
	void drawGround(int gridsize, int scale);
};
#pragma once

#include <gl/glut.h>
#include <vector>
#include "coords.h"
#include <time.h>
#include "RGB.h"
#include "BBoxCoords.h"

/**
* @struct buildingbox
* @brief A struct which is used to track the placment of Buildings in a city.
* @author Morgan Smolder
*/
struct buildingbox{
	///Start x
	int x;
	///Start z
	int z;
	///Width of block
	int width;
	///Depth of block
	int depth;
	///Height of block
	int height;
};

/**
* @struct rectangle3d
* @brief A struct representing a 3D rectangle.
* @author Morgan Smolder
*/
struct rectangle3d{
	///The corners of the rectangle.
	std::vector<point3> corners;
};

/**
* @struct square
* @brief A struct representing a 2D square.
* @author Morgan Smolder
*/
struct square{
	///The corners of the square.
	std::vector<point3> corners;
};

/**
* @class building
* @brief A class which contains methods for procedurally generating buidings in pre-specified sizes.
*
* @author Morgan Smolder
* @version 01
* @date 15/09/2017
*/

class building
{
public:
	building();

	/**
	* @brief Generates a new building.
	*
	* @param b - The building box in which to place the building.
	* @param scale - The scale at which to draw the building.
	*/
	void genBuilding(const buildingbox & b, int scale);

	/**
	* @brief Renders a building in given colors.
	*
	* @param c1 - Color 1
	* @param c2 - Color 2
	* @param c3 - Color 3
	*/
	void renderBuilding(RGB c1, RGB c2, RGB c3);
	
	/**
	* @brief Retrieves the bounding box information from the building class.
	*
	* @return std::vector<BBoxCoords> - A vector of bounding box coordinates for the buiding.
	* @pre The building has already been generated.
	*/
	const std::vector<BBoxCoords>& getBounds() const;

private:
	///The 3d geometry for the buidling.
	std::vector<rectangle3d> geometry;
	///The 2d geometry for the building.
	std::vector<square> squares;
	///The boundinh box information for the building.
	std::vector<BBoxCoords> bounds;


	/**
	* @brief Draws a 3d rectangle.
	*
	* @param xstart - The starting x coordinate.
	* @param ystart - The starting y coordinate.
	* @param zstart - The starting z coordinate.
	* @param width - The width of the rectangle.
	* @param height - The height of the rectangle.
	* @param depth - The depth of the rectangle.
	* @return rectangle3d - The new rectangle struct.
	*/
	const rectangle3d & drawRectangle(float xstart, float ystart, float zstart, float width, float height, float depth);

	/**
	* @brief Returns a random integer in a given range.
	*
	* @param floor - The minimum allowable random value.
	* @param ceiling - The maximum allowable random value.
	* @return int - The randomly generated integer.
	*/
	int genRandInt(int floor, int ceiling);

	/**
	* @brief Renders a 3d rectangle.
	*
	* @param torender - The rectangle object to render.
	*/
	void renderRectangle(const rectangle3d & torender) ;

	/**
	* @brief Draws a 2d square. 
	*
	* @param xstart - The starting x coordinate.
	* @param y - The y coordinate.
	* @param zstart - The starting z coordinate.
	* @param width - The width of the square.
	* @param depth - The depth of the square.
	* @return square - The new square struct.
	*/
	const square & drawSquareXZ(float xstart, float zstart, float y, float width, float depth);

	/**
	* @brief Draws a 2d square.
	*
	* @param xstart - The starting x coordinate.
	* @param ystart - The starting y coordinate.
	* @param z - The z coordinate.
	* @param width - The width of the square.
	* @param height - The height of the square.
	* @return square - The new square struct.
	*/
	const square & drawSquareXY(float xstart, float ystart, float z, float width, float height);

	/**
	* @brief Draws a 2d square.
	*
	* @param x - The x coordinate.
	* @param ystart - The starting y coordinate.
	* @param zstart - The z coordinate.
	* @param height - The height of the square.
	* @param depth - The depth of the square.
	* @return square - The new square struct.
	*/
	const square & drawSquareYZ(float zstart, float ystart, float x, float depth, float height);

	/**
	* @brief Renders a 2d square.
	*
	* @param torender - The square object to render.
	*/
	void renderSquare(const square& torender) ;

	/**
	* @brief Generates the bounding box information for a rectangle.
	*
	* @param xstart - The starting x coordinate.
	* @param zstart - The starting z coordinate.
	* @param width - The width of the rectangle.
	* @param depth - The depth of the rectangle.
	* @param scale - The scale of the rectangle.
	*/
	void genBounds(float startx, float startz, float width, float depth, int scale);
};


#pragma once

#include "building.h"
#include <stack>
#include <algorithm>
#include "objModel.h"

/**
* @struct lnode
* @brief A struct which is used to track the placment of city roads
*		  procedurally generated using an L system.
* @author Morgan Smolder
*/
struct lnode{
	///X axis coordinate
	int x;
	///Y axis coordinate
	int y;
	///Boolean stating wether or not it is a verticle path.
	bool v;
};

/**
* @struct objectLocation
* @brief A struct which is used to track the location and types of obj objects
*		  placed in the procedural city.
* @author Morgan Smolder
*/
struct objectLocation{
	///Translation Matrix
	point3 t;
	///Rotation Matrix
	point3 r;
	///Scale Matrix
	point3 s;
	///Rotation angle to be used with the rotation matrix
	float ra;
	///Determines the color the object should be rendered in
	int c;
	///An index corresponding to a loaded OBJ model in the vector objects
	int objectIndex;
};

/**
* @class city
* @brief A class which contains methods for procedurally generating the buildings,
*		  objects, and paths found in a city.
*
* @author Morgan Smolder
* @version 01
* @date 15/09/2017
*/

class city
{
public:
	city();

	/**
	* @brief Creates the coordinates for a procedural city of given size and scale.
	*		  A wrapper for a number of private methods that perform the actual operations which 
	*		  achieve this.
	*
	* @param gridsize - The size of the grid which should be used to generate the city; this 
	*                   specifies the length and height of the grid.
	* @param scale - The scale at which the city should be drawn. All objects and buildings 
	*                within it are scaled according to this value.
	*/
	void drawCity(int gridsize, int scale);
	
	/**
	* @brief Renders a previously drawn city in colors passed as arguments. 
	*
	* @param c1 - RGB value specifing the color of buildings.
	* @param c2 - RGB value specifing the color of trees.
	* @param c3 - RGB value specifying the color of cars and other objects.
	* @pre The city has already been drawn.
	*/
	void renderCity(RGB c1, RGB c2, RGB c3);

	/**
	* @brief Returns a set of valid coordinates at which a player can be placed in the procedural city.
	*
	* @return point3 - The point where the player should be placed.
	* @pre The city has already been drawn.
	*/
	const point3& getStartCoord() const;

	/**
	* @brief Returns the vector of bounding box coordinates that holds collision information for all objects in the city.
	*
	* @return std::vector<BBoxCoords> - The coordinates of all bounding boxes in the city.
	* @pre The city has already been drawn.
	*/
	const std::vector<BBoxCoords>& getBounds() const;

private:
	///Contains the building objects found in the city
	std::vector<building> buildings;
	///Contains the obj model data to be used with the city
	std::vector<objModel> objects;
	///Contains information on where to place these objects
	std::vector<objectLocation> objectplacement;
	///Contains the bounding box info for everything in the city.
	std::vector<BBoxCoords> bounds;
	///Gives the start coordinates of the player
	point3 startcoord;

	/**
	* @brief Returns a random integer in a given range.
	*
	* @param floor - The minimum allowable random value.
	* @param ceiling - The maximum allowable random value.
	* @return int - The randomly generated integer.
	*/
	int genRandInt(int floor, int ceiling);

	/**
	* @brief Returns a valid point at which to split the grid when drawing a road 
	*        L-System
	*
	* @param prevsplits - A vector containing the previous split locations.
	* @param upper - The upper range for which to check for splittable locations.
	* @param lower - The lower range in which to check for splittable locations.
	* @return int - The new split loction. if one could not be found, this will be negative one.
	*/
	int getSplit(std::vector<int> & prevsplits, int lower, int upper);

	/**
	* @brief Generates the roads in a city using an L-System.
	*
	* @param grid - A 2d grid in which to draw the roads.
	* @pre The grid has been initalised to zero.
	*/
	void genRoads(std::vector<std::vector<int> > & grid);

	/**
	* @brief Expands a vector to a given size and intalises all its elements to zero.
	*
	* @param size - The height and width to expand the grid to.
	* @param grid - The 2d vector to expand.
	*/
	void fillGrid(int size, std::vector<std::vector<int> > & grid);

	/**
	* @brief Generates the alleys in a city
	*
	* @param grid - The 2d grid to fill with alleys
	*/
	void genAlleys(std::vector<std::vector<int> > & grid);

	/**
	* @brief Finds valid start cooordinates at which to place the player in the city.
	*
	* @param scale - The scale of the city.
	* @param grid - The city grid.
	* @pre The grid has been filled with roads.
	*/
	void calcStartCoord(std::vector<std::vector<int> > & grid, int scale);

	/**
	* @brief Finds all the empty spaces in a grid where buildings can be placed.
	*
	* @param scale - The scale of the city.
	* @param grid - The city grid.
	* @param buildingspaces - A vector that will be set to contain the coordinates of empty spaces in the city
	* @pre The grid has been filled with roads and alleys.
	*/
	void findBuildingSpaces(std::vector<std::vector<int> > & grid, std::vector<buildingbox> & buildingspaces, int scale);

	/**
	* @brief Generates all the building objects to be used with the city.
	*
	* @param scale - The scale of the city.
	* @param buildings - A vector in which to place the new building objects.
	* @param buildingspaces - A vector that  contains the coordinates of empty spaces in the city.
	*/
	void genBuildings(std::vector<building> & buildings, const std::vector<buildingbox> & buildingspaces, int scale);

	/**
	* @brief Places all the obj models to be used with the city.
	*
	* @param scale - The scale of the city.
	* @param objectplacement - A vector that will be set to contain the placement information for the new objects.
	* @param buildingspaces - A vector that  contains the coordinates of empty spaces in the city
	*/
	void placeObjects(std::vector<objectLocation> & objectplacement, const std::vector<buildingbox> & buildingspaces, int scale);
	
	/**
	* @brief Generates the bounding boxes for a city.
	*
	* @param scale - The scale of the city.
	* @pre All elements in the city have been generated.
	*/
	void genBounds();
};




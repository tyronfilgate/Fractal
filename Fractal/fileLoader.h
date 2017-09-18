#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>

/**
* @struct point
* @brief A struct which is used to contain 3d coordinate data.
* @author Morgan Smolder
*/
struct point{
	///Coordinate data.
	float x, y, z;
};

/**
* @struct point2d
* @brief A struct which is used to contain 2D coordinate data.
* @author Morgan Smolder
*/
struct point2d{
	///Coordinate data.
	float x, y;
};

/**
* @class fileLoader
* @brief A virtual class which contains static methods for loading data from text files.
*
* @author Morgan Smolder
* @version 01
* @date 15/09/2017
*/

class fileLoader
{
public:
	/**
	* @brief Virtual file loading function, declared so children can inherit it.
	*
	* @param filename - The name of the file to load.
	* @return bool - Indicates wether or not the file was loaded successfully. 
	*/
	virtual bool loadFile(std::string filename) = 0;

protected:
	/**
	* @brief Function that parses coordinates from a string and stores them in a point struct.
	*
	* @param toparse - The string to parse.
	* @param store - The point struct to store the parsed coordinates in. 
	*/
	static void parseCoOrdsXYZ(std::string toparse, point &store);

	/**
	* @brief Function that parses 2d coordinates from a string and stores them in a point struct.
	*
	* @param toparse - The string to parse.
	* @param store - The 2d point struct to store the parsed coordinates in.
	*/
	static void parseCoOrdsXY(std::string toparse, point2d &store);
	
	/**
	* @brief Function that parses a string by moving the traing and ending whitespaces.
	*
	* @param toparse - The string to parse.
	* @param store - The string to store the parsed data in.
	*/
	static void parseString(std::string toparse, std::string &store);

	/**
	* @brief Function that removes unwanted data from a string, including excess white spaces and tab characters.
	*
	* @param line - The line to clean.
	*/
	static void cleanLine(std::string &line);
};


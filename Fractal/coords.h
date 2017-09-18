#pragma once

/**
* @struct point3
* @brief A struct which is used to contain coordinate data.
* @author Morgan Smolder
*/
struct point3{
	///Default constructor.
	point3() : x(0), y(0), z(0){};
	///Parametised constructor.
	point3(float xp, float yp, float zp) : x(xp), y(yp), z(zp){};
	///X coordinate
	float x;
	///Y coordinate
	float y;
	///Z coordinate
	float z;
};
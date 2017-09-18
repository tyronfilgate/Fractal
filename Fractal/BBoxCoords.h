#pragma once

/**
* @struct BBoxCoords
* @brief A struct which encapsulates bounding box data.
* @author Morgan Smolder
*/
struct BBoxCoords{
	///Default constructor.
	BBoxCoords() : minx(0), maxx(0), minz(0), maxz(0){};
	///Minimum x of bounds.
	float minx;
	///Maximum x of bounds.
	float maxx;
	///Minimum z of bounds.
	float minz;
	///Maximum z of bounds.
	float maxz;
};
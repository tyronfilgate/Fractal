#pragma once

struct BBoxCoords{
	BBoxCoords() : minx(0), maxx(0), minz(0), maxz(0){};
	float minx;
	float maxx;
	float minz;
	float maxz;
};
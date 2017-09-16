#pragma once

struct point3{
	point3() : x(0), y(0), z(0){};
	point3(float xp, float yp, float zp) : x(xp), y(yp), z(zp){};
	float x;
	float y;
	float z;
};
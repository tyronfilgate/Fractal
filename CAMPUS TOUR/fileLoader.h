#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>

struct point{
	float x, y, z;
};

struct point2d{
	float x, y;
};

class fileLoader
{
public:
	virtual bool loadFile(std::string filename) = 0;

protected:
	static void parseCoOrdsXYZ(std::string toparse, point &store);
	static void parseCoOrdsXY(std::string toparse, point2d &store);
	static void parseString(std::string toparse, std::string &store);
	static void cleanLine(std::string &line);
};


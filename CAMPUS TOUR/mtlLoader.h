#pragma once

#include <map>
#include <iostream>
#include "fileLoader.h"

//todo - init materials

struct mtlMaterial {
	point Ka;
	point Kd;
	point Ks;
	float d;
	float Ns;
	int illum;
	std::string map_Ka;
	std::string map_Kd;
	std::string map_Ks;
	std::string map_d;
	std::string map_Ns;
	std::string map_bump;
};

class mtlLoader : public fileLoader
{
public:
	mtlLoader();
	bool loadFile(std::string filename);
	const mtlMaterial & getMaterial(std::string materialkey) const;
	bool hasMaterial(std::string materialKey) const;
	void clear();

private:
	std::map<std::string, mtlMaterial> materials;
	bool parseFile(std::ifstream &infile);
};


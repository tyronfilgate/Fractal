#include "mtlLoader.h"


mtlLoader::mtlLoader()
{
}

bool mtlLoader::loadFile(std::string filename) {
	bool inputgood = false;

	std::ifstream infile(filename.c_str());
	if (!infile) return inputgood;

	inputgood = parseFile(infile);

	infile.close();

	return inputgood;
}

bool mtlLoader::parseFile(std::ifstream &infile) {
	std::string currmaterial = "";
	std::string line;
	std::string linefront;

	std::string tempstring;
	point temppoint;

	while (infile.peek() != EOF) {
		getline(infile, line, '\n');

		if (!line.empty()){
			cleanLine(line);
			linefront = line.substr(0, line.find(' '));

			if (linefront == "newmtl") {
				parseString(line, tempstring);
				currmaterial = tempstring;
			}
			else
			if (linefront == "Ka") {
				parseCoOrdsXYZ(line, temppoint);
				materials[currmaterial].Ka = temppoint;
			}
			else
			if (linefront == "Kd") {
				parseCoOrdsXYZ(line, temppoint);
				materials[currmaterial].Kd = temppoint;
			}
			else
			if (linefront == "Ks") {
				parseCoOrdsXYZ(line, temppoint);
				materials[currmaterial].Ks = temppoint;
			}
			else
			if (linefront == "d") {
				parseString(line, tempstring);
				materials[currmaterial].d = atof(tempstring.c_str());
			}
			else
			if (linefront == "Ns") {
				parseString(line, tempstring);
				materials[currmaterial].Ns = atof(tempstring.c_str());
			}
			else
			if (linefront == "illum") {
				parseString(line, tempstring);
				materials[currmaterial].illum = atof(tempstring.c_str());
			}
			else
			if (linefront == "map_Ka") {
				parseString(line, tempstring);
				materials[currmaterial].map_Ka = tempstring.c_str();
			}
			else
			if (linefront == "map_Kd") {
				parseString(line, tempstring);
				materials[currmaterial].map_Kd = tempstring.c_str();
			}
			else
			if (linefront == "map_Ks") {
				parseString(line, tempstring);
				materials[currmaterial].map_Ks = tempstring.c_str();
			}
			else
			if (linefront == "map_Ns") {
				parseString(line, tempstring);
				materials[currmaterial].map_Ns = tempstring.c_str();
			}
			else
			if (linefront == "map_d") {
				parseString(line, tempstring);
				materials[currmaterial].map_d = tempstring.c_str();
			}
			else
			if (linefront == "map_Bump" || linefront == "map_bump") {
				parseString(line, tempstring);
				materials[currmaterial].map_bump = tempstring.c_str();
			}
		}
	}

	if (materials.empty()) {
		return false;
	}
	else {
		return true;
	}
}

const mtlMaterial & mtlLoader::getMaterial(std::string materialkey) const {

	return materials.at(materialkey);
}

bool  mtlLoader::hasMaterial(std::string materialKey) const {

	return (materials.find(materialKey) != materials.end());
}

void mtlLoader::clear(){
	materials.clear();
}
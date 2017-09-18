#include "objLoader.h"

objLoader::objLoader()
{
	mtlfound = false;
}

bool objLoader::loadFile(std::string filename) {

	bool inputgood = false;

	std::ifstream infile(filename.c_str());
	if (!infile) return inputgood;

	std::vector<point> tempvert;
	std::vector<point2d> temptexcord;
	std::vector<point> tempnormals;
	std::vector<facegroup> faces;

	inputgood = parseFile(infile, tempvert, temptexcord, tempnormals, faces);

	infile.close();

	if (inputgood) {
		sortData(tempvert, temptexcord, tempnormals, faces);
	}

	return inputgood;
}

bool objLoader::parseFile(std::ifstream &infile, std::vector<point> &tempvert, std::vector<point2d> &temptexcord, std::vector<point> &tempnormals, std::vector<facegroup > &faces) {

	std::string line;
	std::string linefront;

	point temppoint;
	point2d temp2dpoint;
	facegroup tempfacegroup;
	face tempface;
	std::string tempstring;

	unsigned currgroup = 0;

	unsigned gcount = 0;

	while (infile.peek() != EOF) {

		getline(infile, line, '\n');

		if (!line.empty()){
			cleanLine(line);
			linefront = line.substr(0, line.find(' '));

			if (linefront == "mtllib") {
				parseString(line, tempstring);
				if (!mtlfound) {
					mtlfound = mtlfile.loadFile("./Models/" + tempstring);
				}
			}
			else
			if (linefront == "v") {
				parseCoOrdsXYZ(line, temppoint);
				tempvert.push_back(temppoint);
			}
			else
			if (linefront == "vt") {
				parseCoOrdsXY(line, temp2dpoint);
				temptexcord.push_back(temp2dpoint);
			}
			else
			if (linefront == "vn") {
				parseCoOrdsXYZ(line, temppoint);
				tempnormals.push_back(temppoint);
			}
			else
			if (linefront == "g") {
				if (gcount == 0) {
					gcount++;
					parseString(line, tempstring);
					createNewGroup(tempstring);
				}
				else
				if (!tempfacegroup.empty()) {
					currgroup++;
					parseString(line, tempstring);
					createNewGroup(tempstring);
				}
			}
			else
			if (linefront == "usemtl") {
				parseString(line, tempstring);

				if (gcount == 0) {
					gcount++;
					createNewGroup();
				}
				else
				if (!tempfacegroup.empty()) {
					currgroup++;
					createNewGroup();
				}

				groups.at(currgroup).material = tempstring;
			}
			else
			if (linefront == "f") {

				parseFaces(line, tempface);

				if (gcount == 0) {
					gcount++;
					createNewGroup();
				}
				else
				if (faces.size() < currgroup) {
					faces.push_back(tempfacegroup);
					tempfacegroup.clear();
				}

				if (!tempfacegroup.empty()){
					if (tempface.size() != tempfacegroup.at(tempfacegroup.size() - 1).size()){
						faces.push_back(tempfacegroup);
						tempfacegroup.clear();
						createNewGroup();
						currgroup++;
					}
				}

				tempfacegroup.push_back(tempface);
				tempface.clear();
			}
		}
	}

	if (faces.empty() || faces.size() - 1 < currgroup) {
		faces.push_back(tempfacegroup);
	}

	return true;
}

void objLoader::parseFaces(std::string toparse, face &store) {

	std::string temp;
	static facepoint tempface;

	while (toparse.find(' ') != std::string::npos && toparse.find(' ') != toparse.size() - 1) {
		toparse = toparse.substr(toparse.find(' ') + 1);
		temp = toparse.substr(0, toparse.find(' '));

		if (temp.find('/') != std::string::npos) {
			tempface.push_back(atoi(temp.substr(0, temp.find('/')).c_str()));

			temp = temp.substr(temp.find('/') + 1);

			if (temp.find('/') != std::string::npos) {
				if (temp.at(0) != '/') {
					tempface.push_back(atoi(temp.substr(0, temp.find('/')).c_str()));
				}
				else {
					tempface.push_back(0);
				}

				if (temp.find('/') != std::string::npos) {
					temp = temp.substr(temp.find('/') + 1);
					tempface.push_back(atoi(temp.c_str()));
				}

			}
			else {
				tempface.push_back(atoi(temp.c_str()));
			}

		}
		else
		if (!(temp == "")) {
			tempface.push_back(atoi(temp.c_str()));
		}

		if (!tempface.empty()) {
			store.push_back(tempface);
		}

		tempface.clear();
	}
}

void objLoader::sortData(const std::vector<point> &tempvert, const std::vector<point2d> &temptexcord, const std::vector<point> &tempnormals, const std::vector<facegroup > &faces) {
	for (unsigned i = 0; i < faces.size(); i++) {
		groups.at(i).numface = faces.at(i).at(0).size();
		for (unsigned j = 0; j < faces.at(i).size(); j++) {
			for (unsigned k = 0; k < faces.at(i).at(j).size(); k++) {
				if (faces.at(i).at(j).at(k).at(0) > 0) {
					groups.at(i).vertices.push_back(tempvert.at(faces.at(i).at(j).at(k).at(0) - 1));
				}
				else {
					groups.at(i).vertices.push_back(tempvert.at(tempvert.size() + faces.at(i).at(j).at(k).at(0)));
				}

				if (faces.at(i).at(j).at(k).size() >= 2 && faces.at(i).at(j).at(k).at(1) > 0) {
					groups.at(i).texcoords.push_back(temptexcord.at(faces.at(i).at(j).at(k).at(1) - 1));
				}
				else
				if (faces.at(i).at(j).at(k).size() >= 2 && faces.at(i).at(j).at(k).at(1) != 0) {
					groups.at(i).texcoords.push_back(temptexcord.at(temptexcord.size() + faces.at(i).at(j).at(k).at(1)));
				}

				if (faces.at(i).at(j).at(k).size() >= 3 && faces.at(i).at(j).at(k).at(2) > 0) {
					groups.at(i).normals.push_back(tempnormals.at(faces.at(i).at(j).at(k).at(2) - 1));
				}
				else
				if (faces.at(i).at(j).at(k).size() >= 3) {
					groups.at(i).normals.push_back(tempnormals.at(tempnormals.size() + faces.at(i).at(j).at(k).at(2)));
				}
			}
		}
	}
}

void objLoader::createNewGroup(std::string name){
	rendergroup newgroup;
	newgroup.groupname = name;

	if (!groups.size() == 0){
		if (!groups.at(groups.size() - 1).material.empty()){
			newgroup.material = groups.at(groups.size() - 1).material;
		}
	}

	groups.push_back(newgroup);
}


const std::vector<point>& objLoader::getVertices(unsigned groupno) const {
	return groups.at(groupno).vertices;
}

const std::vector<point2d>& objLoader::getTexCoords(unsigned groupno) const {
	return groups.at(groupno).texcoords;
}

const std::vector<point>& objLoader::getNormals(unsigned groupno) const {
	return groups.at(groupno).normals;
}

unsigned objLoader::getNumFace(unsigned groupno) const {
	return groups.at(groupno).numface;
}

bool objLoader::getMaterial(unsigned groupno, mtlMaterial& store) const {
	if (mtlfile.hasMaterial(groups.at(groupno).material)) {
		store = mtlfile.getMaterial(groups.at(groupno).material);
		return true;
	}
	else {
		return false;
	}
}

unsigned objLoader::getNumGroups() const {
	return groups.size();
}

void objLoader::clear(){
	mtlfound = false;
	mtlfile.clear();
	groups.clear();
}
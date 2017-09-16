#ifndef OBJHANDLE_H
#define OBJHANDLE_H

#include <map>
#include <iostream>
#include "mtlLoader.h"
#include "fileLoader.h"

typedef std::vector<int> facepoint;
typedef std::vector<facepoint> face;
typedef std::vector<face> facegroup;

struct rendergroup {
	std::string groupname;
	std::string material;
	std::vector<point> vertices;
	std::vector<point2d> texcoords;
	std::vector<point> normals;
	unsigned numface;
};

class objLoader : public fileLoader
{
public:
	objLoader();
	bool loadFile(std::string filename);
	const std::vector<point>& getVertices(unsigned groupno = 0) const;
	const std::vector<point2d>& getTexCoords(unsigned groupno = 0) const;
	const std::vector<point>& getNormals(unsigned groupno = 0) const;
	bool getMaterial(unsigned groupno, mtlMaterial& store) const;
	unsigned getNumFace(unsigned groupno = 0) const;
	unsigned getNumGroups() const;
	void clear();

private:
	std::vector<rendergroup> groups;
	mtlLoader mtlfile;
	bool mtlfound;
	bool parseFile(std::ifstream &infile, std::vector<point> &tempvert, std::vector<point2d> &temptexcord, std::vector<point> &tempnormals, std::vector<facegroup> &faces);
	static void parseFaces(std::string toparse, face &store);
	void sortData(const std::vector<point> &tempvert, const std::vector<point2d> &temptexcord, const std::vector<point> &tempnormals, const std::vector<facegroup> &faces);
	void createNewGroup(std::string name = "Default");
};

#endif // OBJHANDLE_H

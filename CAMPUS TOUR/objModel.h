#pragma once

#include "objLoader.h"
#include "GL/glut.h"
#include "coords.h"
#include "RGB.h"
#include "BBoxCoords.h"

struct TGAFile{
	GLubyte* data;
	unsigned pixelsize;
	unsigned width;
	unsigned height;
};

class objModel
{
public:
	objModel();
	objModel(std::string filename);
	bool loadOBJ(std::string filename);
	void createDisplayList(const int &listno, point3 translate = point3(), point3 scale = point3(), point3 rotate = point3(), float rotateamount = 0);
	void createWireFrameDisplayList(const int &listno, RGB c, point3 translate = point3(), point3 scale = point3(), point3 rotate = point3(), float rotateamount = 0);
	void renderModel(point3 translate = point3(), point3 scale = point3(), point3 rotate = point3(), float rotateamount = 0);
	void renderWireFrameModel(RGB c, point3 translate = point3(), point3 scale = point3(), point3 rotate = point3(), float rotateamount = 0);
	void setStartTex(unsigned newstart);
	void clear();
	const BBoxCoords & getBounds() const;

private:
	unsigned starttex;
	std::map<std::string, unsigned> texIDs;
	objLoader objfile;
	BBoxCoords bounds;
	bool addTextureID(std::string newtexture);
	bool loadTGATexture(unsigned& texID, std::string filename);
	void createTexture(unsigned& texID, TGAFile imagedata);
	void freeImage(TGAFile imagedata);
	void genBounds();

};


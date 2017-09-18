#include "building.h"


building::building()
{
	time_t t;

	srand((unsigned)time(&t));
}

void building::genBuilding(const buildingbox & b, int scale){

	int size = b.height;

	geometry.push_back(drawRectangle(b.x, 0, b.z, b.width, scale / 10, b.depth));

	if ((b.width / scale) > 4 && (b.depth / scale) > 4){
		if (size > scale * 10){
			for (unsigned i = scale * 3; i < size; i = i + scale){
				squares.push_back(drawSquareXZ(b.x + scale*1.5, b.z + scale*1.5, i, b.width - (scale)* 3, b.depth - (scale)* 3));
			}
			for (unsigned i = b.z + scale * 1.5; i <= (b.z + b.depth - (scale)* 3); i = i + scale*1.5){
				squares.push_back(drawSquareXY(b.x + scale*1.5, scale * 3, i, b.width - (scale)* 3, size - scale * 3));
			}
			for (unsigned i = b.x + scale * 1.5; i <= (b.x + b.width - (scale)* 3); i = i + scale*1.5){
				squares.push_back(drawSquareYZ(b.z + scale*1.5, scale * 3, i, b.depth - (scale)* 3, size - scale * 3));
			}
			geometry.push_back(drawRectangle(b.x + scale, scale / 10, b.z + scale, b.width - (scale)* 2, scale * 3, b.depth - (scale)* 2));
			genBounds(b.x + scale, b.z + scale, b.width - (scale)* 2, b.depth - (scale)* 2, scale);
			geometry.push_back(drawRectangle(b.x + scale*1.5, scale / 10, b.z + scale*1.5, b.width - (scale)* 3, size, b.depth - (scale)* 3));
		}
		else{
				float x, z, w, d;
				size = genRandInt(scale * 3, scale * 10);
				x = b.x + scale;
				z = b.z + scale;
				w = (b.width - (scale)* 2) / 2;
				d = (b.depth - (scale)* 2) / 2;
				geometry.push_back(drawRectangle(x, scale / 10, z, w, size, d));
				geometry.push_back(drawRectangle(x - (scale / 5), scale / 10, (z - scale / 5), scale, size, scale));
				geometry.push_back(drawRectangle(x + w - scale + (scale / 5), scale / 10, z + d - scale + (scale / 5), scale, size, scale));
				geometry.push_back(drawRectangle(x - (scale / 5), scale / 10, z + d - scale + (scale / 5), scale, size, scale));
				geometry.push_back(drawRectangle(x + w - scale + (scale / 5), scale / 10, z - (scale / 5), scale, size, scale));
				for (unsigned i = scale * 3; i < size; i += scale){
					squares.push_back(drawSquareXZ(x, z, i, w, d));
				}
				genBounds(b.x + scale, b.z + scale, (b.width - (scale)* 2) / 2, (b.depth - (scale)* 2) / 2, scale);
				size = genRandInt(scale * 3, scale * 10);
				x = b.x + scale * 2 + (b.width - (scale)* 2) / 2;
				z = b.z + scale;
				w = (b.width - (scale)* 4) / 2;
				d = (b.depth - (scale)* 2) / 2;
				geometry.push_back(drawRectangle(x, scale / 10, z, w, size, d));
				for (unsigned i = scale * 2; i < size; i += scale){
					geometry.push_back(drawRectangle(x - scale / 5, i, z - scale / 5, w + (scale / 5) * 2, scale / 4, d + (scale / 5) * 2));
				}
				genBounds(b.x + scale * 2 + (b.width - (scale)* 2) / 2, b.z + scale, (b.width - (scale)* 4) / 2, (b.depth - (scale)* 2) / 2, scale);
				size = genRandInt(scale * 3, scale * 10);
				x = b.x + scale * 2 + (b.width - (scale)* 2) / 2;
				z = b.z + scale * 2 + (b.depth - (scale)* 2) / 2;
				w = (b.width - (scale)* 4) / 2;
				d = (b.depth - (scale)* 4) / 2;
				geometry.push_back(drawRectangle(x, scale / 10, z, w, size, d));
				genBounds(b.x + scale * 2 + (b.width - (scale)* 2) / 2, b.z + scale * 2 + (b.depth - (scale)* 2) / 2, (b.width - (scale)* 4) / 2, (b.depth - (scale)* 4) / 2, scale);
				size = genRandInt(scale * 3, scale * 10);
				geometry.push_back(drawRectangle(b.x + scale, scale / 10, b.z + scale * 2 + (b.depth - (scale)* 2) / 2, (b.width - (scale)* 2) / 2, size, (b.depth - (scale)* 4) / 2));
				genBounds(b.x + scale, b.z + scale * 2 + (b.depth - (scale)* 2) / 2, (b.width - (scale)* 2) / 2, (b.depth - (scale)* 4) / 2, scale);
		}
	}
}

void building::genBounds(float startx, float startz, float width, float depth, int scale){
	static BBoxCoords tempbb;

	tempbb.maxx = startx + width;
	tempbb.minx = startx;
	tempbb.maxz = startz + scale*.8;
	tempbb.minz = startz;

	bounds.push_back(tempbb);

	tempbb.maxx = startx + scale*0.8;
	tempbb.minx = startx;
	tempbb.maxz = startz + depth;
	tempbb.minz = startz;

	bounds.push_back(tempbb);

	tempbb.maxx = startx + width;
	tempbb.minx = startx + width - scale*0.8;
	tempbb.maxz = startz + depth;
	tempbb.minz = startz;

	bounds.push_back(tempbb);

	tempbb.maxx = startx + width;
	tempbb.minx = startx;
	tempbb.maxz = startz + depth;
	tempbb.minz = startz + depth - scale*0.8;

	bounds.push_back(tempbb);
}

int building::genRandInt(int floor, int ceiling){
	float range = ceiling - floor;

	return (int)floor + (float)((range * rand()) / (RAND_MAX + 1));
}

const std::vector<BBoxCoords>& building::getBounds() const{
	return bounds;
}


void building::renderBuilding(RGB c1, RGB c2, RGB c3) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(0.5);
	glColor3f(c1.r, c1.g, c1.b);
	for (unsigned i = 0; i < geometry.size(); i++){
		renderRectangle(geometry.at(i));
	}
	for (unsigned i = 0; i < squares.size(); i++){
		renderSquare(squares.at(i));
	}
	glPolygonOffset(1, 1);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0, 0, 0);
	for (unsigned i = 0; i < geometry.size(); i++){
		renderRectangle(geometry.at(i));
	}
	glDisable(GL_POLYGON_OFFSET_FILL);
}

const rectangle3d & building::drawRectangle(float xstart, float ystart, float zstart, float width, float height, float depth){
	static rectangle3d tempr;
	static point3 temppoint;

	tempr.corners.clear();

	temppoint.x = xstart;
	temppoint.y = ystart;
	temppoint.z = zstart;

	tempr.corners.push_back(temppoint);

	temppoint.x = xstart + width;
	temppoint.y = ystart;
	temppoint.z = zstart;

	tempr.corners.push_back(temppoint);

	temppoint.x = xstart;
	temppoint.y = ystart + height;
	temppoint.z = zstart;

	tempr.corners.push_back(temppoint);

	temppoint.x = xstart + width;
	temppoint.y = ystart + height;
	temppoint.z = zstart;

	tempr.corners.push_back(temppoint);

	temppoint.x = xstart;
	temppoint.y = ystart;
	temppoint.z = zstart + depth;

	tempr.corners.push_back(temppoint);

	temppoint.x = xstart + width;
	temppoint.y = ystart;
	temppoint.z = zstart + depth;

	tempr.corners.push_back(temppoint);

	temppoint.x = xstart;
	temppoint.y = ystart + height;
	temppoint.z = zstart + depth;

	tempr.corners.push_back(temppoint);

	temppoint.x = xstart + width;
	temppoint.y = ystart + height;
	temppoint.z = zstart + depth;

	tempr.corners.push_back(temppoint);

	return tempr;
}

void building::renderRectangle(const rectangle3d & torender) {
	glBegin(GL_QUADS);
	glVertex3f(torender.corners.at(0).x, torender.corners.at(0).y, torender.corners.at(0).z);
	glVertex3f(torender.corners.at(1).x, torender.corners.at(1).y, torender.corners.at(1).z);
	glVertex3f(torender.corners.at(3).x, torender.corners.at(3).y, torender.corners.at(3).z);
	glVertex3f(torender.corners.at(2).x, torender.corners.at(2).y, torender.corners.at(2).z);

	glVertex3f(torender.corners.at(0).x, torender.corners.at(0).y, torender.corners.at(0).z);
	glVertex3f(torender.corners.at(2).x, torender.corners.at(2).y, torender.corners.at(2).z);
	glVertex3f(torender.corners.at(6).x, torender.corners.at(6).y, torender.corners.at(6).z);
	glVertex3f(torender.corners.at(4).x, torender.corners.at(4).y, torender.corners.at(4).z);

	glVertex3f(torender.corners.at(0).x, torender.corners.at(0).y, torender.corners.at(0).z);
	glVertex3f(torender.corners.at(1).x, torender.corners.at(1).y, torender.corners.at(1).z);
	glVertex3f(torender.corners.at(5).x, torender.corners.at(5).y, torender.corners.at(5).z);
	glVertex3f(torender.corners.at(4).x, torender.corners.at(4).y, torender.corners.at(4).z);

	glVertex3f(torender.corners.at(1).x, torender.corners.at(1).y, torender.corners.at(1).z);
	glVertex3f(torender.corners.at(3).x, torender.corners.at(3).y, torender.corners.at(3).z);
	glVertex3f(torender.corners.at(7).x, torender.corners.at(7).y, torender.corners.at(7).z);
	glVertex3f(torender.corners.at(5).x, torender.corners.at(5).y, torender.corners.at(5).z);

	glVertex3f(torender.corners.at(2).x, torender.corners.at(2).y, torender.corners.at(2).z);
	glVertex3f(torender.corners.at(3).x, torender.corners.at(3).y, torender.corners.at(3).z);
	glVertex3f(torender.corners.at(7).x, torender.corners.at(7).y, torender.corners.at(7).z);
	glVertex3f(torender.corners.at(6).x, torender.corners.at(6).y, torender.corners.at(6).z);

	glVertex3f(torender.corners.at(4).x, torender.corners.at(4).y, torender.corners.at(4).z);
	glVertex3f(torender.corners.at(5).x, torender.corners.at(5).y, torender.corners.at(5).z);
	glVertex3f(torender.corners.at(7).x, torender.corners.at(7).y, torender.corners.at(7).z);
	glVertex3f(torender.corners.at(6).x, torender.corners.at(6).y, torender.corners.at(6).z);
	glEnd();
}

const square & building::drawSquareXZ(float xstart, float zstart, float y, float width, float depth){
	static square temps;
	static point3 temppoint;

	temps.corners.clear();

	temppoint.x = xstart;
	temppoint.y = y;
	temppoint.z = zstart;

	temps.corners.push_back(temppoint);

	temppoint.x = xstart + width;
	temppoint.y = y;
	temppoint.z = zstart;

	temps.corners.push_back(temppoint);

	temppoint.x = xstart;
	temppoint.y = y;
	temppoint.z = zstart + depth;

	temps.corners.push_back(temppoint);

	temppoint.x = xstart + width;
	temppoint.y = y;
	temppoint.z = zstart + depth;

	temps.corners.push_back(temppoint);

	return temps;
}

const square & building::drawSquareXY(float xstart, float ystart, float z, float width, float height){
	static square temps;
	static point3 temppoint;

	temps.corners.clear();

	temppoint.x = xstart;
	temppoint.y = ystart;
	temppoint.z = z;

	temps.corners.push_back(temppoint);

	temppoint.x = xstart + width;
	temppoint.y = ystart;
	temppoint.z = z;

	temps.corners.push_back(temppoint);

	temppoint.x = xstart;
	temppoint.y = ystart + height;
	temppoint.z = z;

	temps.corners.push_back(temppoint);

	temppoint.x = xstart + width;
	temppoint.y = ystart + height;
	temppoint.z = z;

	temps.corners.push_back(temppoint);

	return temps;
}

const square & building::drawSquareYZ(float zstart, float ystart, float x, float depth, float height){
	static square temps;
	static point3 temppoint;

	temps.corners.clear();

	temppoint.x = x;
	temppoint.y = ystart;
	temppoint.z = zstart;

	temps.corners.push_back(temppoint);

	temppoint.x = x;
	temppoint.y = ystart;
	temppoint.z = zstart + depth;

	temps.corners.push_back(temppoint);

	temppoint.x = x;
	temppoint.y = ystart + height;
	temppoint.z = zstart;

	temps.corners.push_back(temppoint);

	temppoint.x = x;
	temppoint.y = ystart + height;
	temppoint.z = zstart + depth;

	temps.corners.push_back(temppoint);

	return temps;
}

void building::renderSquare(const square& torender) {
	glBegin(GL_QUADS);
	glVertex3f(torender.corners.at(0).x, torender.corners.at(0).y, torender.corners.at(0).z);
	glVertex3f(torender.corners.at(1).x, torender.corners.at(1).y, torender.corners.at(1).z);
	glVertex3f(torender.corners.at(3).x, torender.corners.at(3).y, torender.corners.at(3).z);
	glVertex3f(torender.corners.at(2).x, torender.corners.at(2).y, torender.corners.at(2).z);
	glEnd();
}

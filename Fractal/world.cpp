#include "world.h"


void world::genWorld(int size, int scale){
	int randc;

	time_t t;

	srand((unsigned)time(&t));


	randc = rand() % 4;

	randc = 0;

	switch (randc){
	case 0:
		c1.r = 0.027;
		c1.g = 0.589;
		c1.b = 0.777;

		c2.r = 0.9;
		c2.g = 0;
		c2.b = 0.5;

		c3.r = 0.9;
		c3.g = 0;
		c3.b = 0.5;
		break;
	case 1:
		c1.r = 0.9;
		c1.g = 0.9;
		c1.b = 0.9;

		c3.r = 1;
		c3.g = 0;
		c3.b = 0.3;

		c2.r = 0.7;
		c2.g = 0.7;
		c2.b = 0.7;
		break;
	case 2:
		c1.r = 1;
		c1.g = 0.35;
		c1.b = 0;

		c2.r = 0;
		c2.g = 0.1;
		c2.b = 0.8;

		c3.r = 0.2;
		c3.g = 0.1;
		c3.b = 1;
		break;
	default:
		c1.r = .849;
		c1.g = .849;
		c1.b = .08;

		c2.r = .5;
		c2.g = 0;
		c2.b = .5;

		c3.r = .5;
		c3.g = 0;
		c3.b = .5;
	}

	BBoxCoords tempBB;

	tempBB.minx = 0;
	tempBB.maxx = (float) (pow(2, size) + 1)* (float) scale;
	tempBB.minz = 0;
	tempBB.maxz = (float) scale* (float) 0.8;

	bounds.push_back(tempBB);

	tempBB.minx = 0;
	tempBB.maxx = (float) scale* (float) 0.8;
	tempBB.minz = 0;
	tempBB.maxz = (float) (pow(2, size) + 1)* (float)scale;

	bounds.push_back(tempBB);

	tempBB.minx = (float)(pow(2, size) + 1)* (float)scale - scale*  (float)1.6;
	tempBB.maxx = (float)(pow(2, size) + 1)* (float)scale - scale*  (float)0.8;
	tempBB.minz = 0;
	tempBB.maxz = (float) (pow(2, size) + 1)* (float) scale;

	bounds.push_back(tempBB);

	tempBB.minx = 0;
	tempBB.maxx = (float)(pow(2, size) + 1)*  (float)scale;
	tempBB.minz = (float)(pow(2, size) + 1)* (float)scale - scale*  (float)1.6;
	tempBB.maxz = (float)(pow(2, size) + 1)* (float)scale - scale* (float)0.8;

	bounds.push_back(tempBB);

	f.drawFractals(size, scale);
	c.drawCity(size, scale);

	for (unsigned i = 0; i < c.getBounds().size(); i++){
		bounds.push_back(c.getBounds().at(i));
	}

	drawGround(size, scale);
}

void world::createDisplayList(const int & listno){
	glNewList(listno, GL_COMPILE);
	f.renderFractals(c1, c2, c3);
	c.renderCity(c1, c2, c3);

	drawPlain(vertices, indices, c3);

	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	drawPlain(vertices, indices, c3);
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glRotatef(-90, 0, 0, 1);
	drawPlain(vertices, indices, c3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(vertices.at(vertices.size() - 1).x, 0, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(-90, 0, 0, 1);
	drawPlain(vertices, indices, c3);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, vertices.at(vertices.size() - 1).z);
	glRotatef(-90, 1, 0, 0);
	drawPlain(vertices, indices, c3);
	glPopMatrix();

	glEndList();
}

const point3& world::getStartCoord() const{
	return c.getStartCoord();
}

void world::drawPlain(std::vector<point3> & vertices, std::vector<int> & indices, RGB c3){
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(0.5);
	glColor3f(c3.r, c3.g, c3.b);
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned i = 0; i < indices.size(); i++){
		glVertex3f(vertices.at(indices.at(i)).x, vertices.at(indices.at(i)).y, vertices.at(indices.at(i)).z);
	}
	glEnd();
	glPolygonOffset(1, 1);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0, 0, 0);
	for (unsigned i = 0; i < indices.size(); i++){
		glVertex3f(vertices.at(indices.at(i)).x, vertices.at(indices.at(i)).y, vertices.at(indices.at(i)).z);
	}
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
}

void world::genPlaneVerticesXZ(int min1, int max1, int min2, int max2, std::vector<point3> & coords, int scale){
	static point3 tempoint;

	for (int i = min1; i < max1; i++){
		for (int j = min2; j < max2; j++){
			tempoint.x = i*scale;
			tempoint.y = 0;
			tempoint.z = j*scale;
			coords.push_back(tempoint);
		}
	}
}


void world::genPlaneIndices(int min, int max, std::vector<int> & indices){
	int size = pow(2, (max)) + 1;

	for (int i = 0; i < size - 1; i++) {
		if (i % 2 == 0) {
			for (int j = 0; j < size; j++) {
				indices.push_back(j + i * size);
				indices.push_back(j + (i + 1) * size);
			}
		}
		else {
			for (int j = size - 1; j > 0; j--) {
				indices.push_back(j + (i + 1) * size);
				indices.push_back(j - 1 + i * size);
			}
		}
	}
}

const std::vector<BBoxCoords> & world::getBounds() {
	return bounds;
}

void world::drawGround(int gridsize, int scale){

	genPlaneVerticesXZ(0, (pow(2, (gridsize)) + 1), 0, (pow(2, (gridsize)) + 1), vertices, scale);
	genPlaneIndices(0, gridsize, indices);
}
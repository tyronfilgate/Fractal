#include "fractalGenerator.h"


fractalGenerator::fractalGenerator()
{
	time_t t;

	srand((unsigned)time(&t));
	//srand(43);
}

void fractalGenerator::genPlaneVertices(int min1, int max1, int min2, int max2, std::vector<point3> & coords, int scale){
	static point3 tempoint;

	for (unsigned i = min1; i < max1; i++){
		for (unsigned j = min2; j < max2; j++){
			tempoint.x = i*scale;
			tempoint.y = 0;
			tempoint.z = j*scale;
			coords.push_back(tempoint);
		}
	}
}

void fractalGenerator::genPlaneIndices(int min, int max, std::vector<int> & indices){
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

void fractalGenerator::genDiamondSquare(int size, int lowerrange, int upperrange, std::vector<point3> & coords, unsigned coordsstart){
	size = pow(2, (size)) + 1;

	float** grid = new float*[size];
	for (int i = 0; i < size; i++) grid[i] = new float[size];

	grid[0][0] = genRand(lowerrange, upperrange);
	grid[0][size - 1] = genRand(lowerrange, upperrange);
	grid[size - 1][size - 1] = genRand(lowerrange, upperrange);
	grid[size - 1][0] = genRand(lowerrange, upperrange);

	int increment = size - 1;

	float center = 0;

	bool hasstepped;
	int count;

	lowerrange = -10 * 250;
	upperrange = 10 * 250;

	while (increment > 1){
		for (int i = increment / 2; i < size - 1; i = i + increment){
			for (int j = increment / 2; j < size; j = j + increment){
				center += grid[i - increment / 2][j - increment / 2];
				center += grid[i + increment / 2][j + increment / 2];
				center += grid[i - increment / 2][j + increment / 2];
				center += grid[i + increment / 2][j - increment / 2];
				center = center / 4;
				center = center + genRand(lowerrange, upperrange);
				grid[i][j] = center;
				center = 0;
			}
		}

		hasstepped = false;
		count = 0;
		for (int i = 0; i < size; i = i + increment / 2){
			for (int j = ((!hasstepped) ? increment / 2 : 0); (!hasstepped && j < size - 1) || (hasstepped && j < size); j = j + increment){
				if (j - increment / 2 >= 0){
					center += grid[i][j - increment / 2];
					count++;
				}
				if (i + increment / 2 < size){
					center += grid[i + increment / 2][j];
					count++;
				}
				if (j + increment / 2 < size) {
					center += grid[i][j + increment / 2];
					count++;
				}
				if (i - increment / 2 >= 0){
					center += grid[i - increment / 2][j];
					count++;;
				}
				center = center / count;
				center = center + genRand(lowerrange, upperrange);
				grid[i][j] = center;
				center = 0;
				count = 0;
			}
			hasstepped = !hasstepped;
		}

		increment = increment / 2;

		lowerrange += 0.01;
		upperrange -= 0.01;
	}

	for (int i = 0; i < size; i++){
		for (int j = 0; j <size; j++){
			coords.at(coordsstart++).y = grid[i][j];
		}
	}

	for (int i = 0; i < size; i++) delete[] grid[i];
	delete[] grid;
}

float fractalGenerator::genRand(int floor, int ceiling){

	float range = ceiling - floor;

	return floor + (float)((range * rand()) / (RAND_MAX + 1));
}

void fractalGenerator::drawFractals(int gridsize, int scale){

	genPlaneVertices(0, (pow(2, (gridsize)) + 1), 0, (pow(2, (gridsize)) + 1), vertices, scale);
	genPlaneIndices(0, gridsize, indices);
	genDiamondSquare(gridsize, scale * 25, scale * 30, vertices, 0);
}

void fractalGenerator::renderFractals(RGB c1, RGB c2, RGB c3){

	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(0.5);
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned i = 0; i < indices.size(); i++){
		if (vertices.at(indices.at(i)).y < 30000){
			glColor3f(c1.r, c1.g, c1.b);
		}
		else if (vertices.at(indices.at(i)).y < 35000){
			glColor3f(c2.r, c2.g, c2.b);
		}
		else{
			glColor3f(0, 0, 0);
		}
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

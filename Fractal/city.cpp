
#include "city.h"


city::city()
{
	time_t t;

	srand((unsigned)time(&t));

	objModel m;
	m.loadOBJ("./Models/palmtree.obj");
	objects.push_back(m);
	m.clear();

	m.loadOBJ("./Models/trafficlight.obj");
	objects.push_back(m);
	m.clear();

	m.loadOBJ("./Models/entrance.obj");
	objects.push_back(m);
	m.clear();

	m.loadOBJ("./Models/car.obj");
	objects.push_back(m);
	m.clear();

	m.loadOBJ("./Models/lamp.obj");
	objects.push_back(m);
	m.clear();

	m.loadOBJ("./Models/window.obj");
	objects.push_back(m);
	m.clear();

	m.loadOBJ("./Models/door.obj");
	objects.push_back(m);
	m.clear();
}

int city::genRandInt(int floor, int ceiling){
	float range = (float) ceiling - floor;

	return (int) (floor + ((range * rand()) / (RAND_MAX + 1)));
}

const point3& city::getStartCoord() const{
	return startcoord;
}

int city::getSplit(std::vector<int> & prevsplits, int lower, int upper){
	int split = -1;

	if (!prevsplits.empty()){
		std::sort(prevsplits.begin(), prevsplits.end());
		if (prevsplits.at(0) > lower + 6){
			split = genRandInt(lower, prevsplits.at(0) - 6);
		}
		else
		if (prevsplits.at(prevsplits.size() - 1) < upper - 6){
			split = genRandInt(prevsplits.at(prevsplits.size() - 1) + 6, upper);
		}
	}
	else{
		split = genRandInt(lower, upper);
	}

	return split;
}

void city::genRoads(std::vector<std::vector<int> > & grid){

	lnode A;

	A.x = grid.size() / 2;
	A.y = grid.size() / 2;
	A.v = true;

	std::stack<lnode> s;
	s.push(A);

	std::stack<lnode> temps;
	int upper, lower;

	int split = 1;

	bool met;

	bool even = true;

	std::vector<int> xsplits;
	std::vector<int> ysplits;

	while (split != -1) {

		while (!s.empty()){
			met = false;
			if (s.top().v == true){
				A.x = s.top().x - s.top().x / 2;
				A.y = s.top().y;
				lower = A.x;
				A.v = false;
				temps.push(A);
				A.x = s.top().x + s.top().x / 2;
				A.y = s.top().y;
				upper = A.x;
				temps.push(A);

				split = getSplit(xsplits, lower, upper);

				if (split != -1){

					xsplits.push_back(split);

					if (split > 1 && split < (int) grid.size() - 2){
						for (int i = even ? 0 : grid.size() - 1; ((even && i < (int) grid.size()) || (!even && i > 0)) && !met; even ? i++ : i--){
							for (int j = split - 1; j < split + 2 && !met; j++){
								if (grid.at(i).at(j) == 1){
									met = true;
									even = !even;
								}
								else{
									grid.at(i).at(j) = 1;
								}
							}
						}
					}
				}

				s.pop();
			}
			else{
				A.y = s.top().y - s.top().y / 2;
				A.x = s.top().x;
				lower = A.y;
				A.v = true;
				temps.push(A);
				A.y = s.top().y + s.top().y / 2;
				upper = A.y;
				A.x = s.top().x;
				temps.push(A);

				split = getSplit(ysplits, lower, upper);

				if (split != -1){
					ysplits.push_back(split);

					if (split < ((int) grid.size() - 2) && split > 1){
						for (int i = split; i < (int) split + 1 && !met; i++){
							for (unsigned j = even ? 0 : grid.size() - 1; ((even && j < grid.size()) || (!even && j > 0)) && !met; even ? j++ : j--){
								if (grid.at(i).at(j) == 1){
									met = true;
									even = !even;
								}
								else{
									grid.at(i - 1).at(j) = 1;
									grid.at(i).at(j) = 1;
									grid.at(i + 1).at(j) = 1;
								}
							}
						}
					}
				}

				s.pop();
			}
		}

		while (!temps.empty()){
			s.push(temps.top());
			temps.pop();
		}
	}
}

void city::fillGrid(int size, std::vector<std::vector<int> > & grid){

	size = (int) pow(2, (size)) + 1;

	std::vector<int> emptyvec;

	for (int i = 0; i < size; i++){
		grid.push_back(emptyvec);
		for (int j = 0; j < size; j++){
			grid.at(i).push_back(0);
		}
	}

}

void city::genAlleys(std::vector<std::vector<int> > & grid){

	int start = 3;

	for (unsigned j = start; j < grid.size() - 3; j += genRandInt(7, 15)){
		for (unsigned i = 0; i < grid.size(); i++){
			if (grid.at(j - 1).at(i) == 0 && grid.at(j - 2).at(i) == 0 && grid.at(j - 3).at(i) == 0 && grid.at(j).at(i) == 0
				&& grid.at(j + 1).at(i) == 0 && grid.at(j + 2).at(i) == 0 && grid.at(j + 3).at(i) == 0){
				grid.at(j).at(i) = 1;
			}
		}
	}

	for (unsigned j = start; j < grid.size() - 3; j += genRandInt(9, 17)){
		for (int i = 0; i < genRandInt(0, grid.size()); i++){
			if (grid.at(i).at(j - 1) == 0 && grid.at(i).at(j - 2) == 0 && grid.at(i).at(j - 3) == 0 && grid.at(i).at(j) == 0
				&& grid.at(i).at(j + 1) == 0 && grid.at(i).at(j + 2) == 0 && grid.at(i).at(j + 3) == 0){
				grid.at(i).at(j) = 1;
			}
		}
	}

	for (unsigned j = start; j < grid.size() - 3; j += genRandInt(9, 17)){
		for (int i = grid.size() - 1; i > genRandInt(0, grid.size()); i--){
			if (grid.at(i).at(j - 1) == 0 && grid.at(i).at(j - 2) == 0 && grid.at(i).at(j - 3) == 0 && grid.at(i).at(j) == 0
				&& grid.at(i).at(j + 1) == 0 && grid.at(i).at(j + 2) == 0 && grid.at(i).at(j + 3) == 0){
				grid.at(i).at(j) = 1;
			}
		}
	}
}

void city::calcStartCoord(std::vector<std::vector<int> > & grid, int scale){
	bool found = false;
	for (unsigned i = 1; i < grid.size() - 1 && found == false; i++){
		for (unsigned j = grid.size(); j < grid.size() - 1 && found == false; j++){
			if (grid.at(j).at(i) == 1 && grid.at(j).at(i + 1) == 1 && grid.at(j).at(i - 1) == 1){
				startcoord.x = (float) i * scale;
				startcoord.z = (float) j * scale;
				startcoord.y = 450;
				found = true;
			}
		}
	}

	if (!found){
		for (unsigned i = 1; i < grid.size() - 1 && found == false; i++){
			for (unsigned j = 1; j < grid.size() - 1 && found == false; j++){
				if (grid.at(j).at(i) == 1 && grid.at(j).at(i + 1) == 1 && grid.at(j).at(i - 1) == 1){
					startcoord.x = (float) i * scale;
					startcoord.z = (float) j * scale;
					startcoord.y = 450;
					found = true;
				}
			}
		}
	}
}

void city::findBuildingSpaces(std::vector<std::vector<int> > & grid, std::vector<buildingbox> & buildingspaces, int scale){

	static buildingbox b;

	bool found = false;


	for (int i = 0; i < (int) grid.size(); i++){
		for (int j = 0; j < 1; j++){
			grid.at(i).at(j) = 1;
		}
	}

	for (int i = 0; i < (int) grid.size(); i++){
		for (int j = grid.size() - 1; j < (int)grid.size(); j++){
			grid.at(i).at(j) = 1;
		}
	}

	for (int i = 0; i < (int) grid.size(); i++){
		for (int j = 0; j < 1; j++){
			grid.at(j).at(i) = 1;
		}
	}

	for (int i = 0; i < (int) grid.size(); i++){
		for (int j = grid.size() - 1; j < (int) grid.size(); j++){
			grid.at(j).at(i) = 1;
		}
	}

	for (int i = 0; i < (int) grid.size(); i++){
		for (int j = 0; j < (int) grid.size(); j++){
			if (grid.at(i).at(j) == 0){
				b.z = i * scale;
				b.x = j * scale;
				for (unsigned k = i; k < grid.size() && found == false; k++){
					if (grid.at(k).at(j) == 1){
						b.depth = (k - i) * scale;
						found = true;
					}
					else{
						grid.at(k).at(j) = 2;
					}
				}

				if (found == false){
					b.depth = (grid.size() - i) * scale;
				}
				else{
					found = false;
				}

				for (unsigned k = j; k < grid.size() && !found; k++){
					if (grid.at(i).at(k) == 1){
						b.width = (k - j) * scale;
						found = true;
					}
					else{
						grid.at(i).at(k) = 2;
					}
				}

				if (found == false){
					b.width = (grid.size() - j) * scale;
				}
				else{
					found = false;
				}

				for (int k = i; k < (int)i + b.depth / scale; k++){
					for (int l = j; l < (int)j + b.width / scale; l++){
						grid.at(k).at(l) = 2;
					}
				}

				b.height = genRandInt(scale * 5, scale * 18);

				buildingspaces.push_back(b);
			}
		}
	}
}

void city::genBuildings(std::vector<building> & buildings, const std::vector<buildingbox> & buildingspaces, int scale){
	static building b;
	for (unsigned i = 0; i < buildingspaces.size(); i++){
		b.genBuilding(buildingspaces.at(i), scale);
		buildings.push_back(b);
	}
}

const std::vector<BBoxCoords>& city::getBounds() const{
	return bounds;
}

void city::placeObjects(std::vector<objectLocation> & objectplacement, const std::vector<buildingbox> & buildingspaces, int scale){
	objectLocation tempol;

	//trafficlights
	for (unsigned i = 0; i < buildingspaces.size(); i++){
		tempol.t.x = buildingspaces.at(i).x + (float) scale / 2;
		tempol.t.y = (float) scale / 10;
		tempol.t.z = buildingspaces.at(i).z + (float) scale / 2;

		tempol.c = 1;

		tempol.s.x = (float) scale;
		tempol.s.y = (float) scale;
		tempol.s.z = (float) scale;
		tempol.objectIndex = 1;
		objectplacement.push_back(tempol);

		if ((buildingspaces.at(i).width / scale) > 4 && (buildingspaces.at(i).depth / scale) > 4){

			//lamps z
			for (int j = buildingspaces.at(i).z + scale * 2; j < buildingspaces.at(i).z + buildingspaces.at(i).depth - scale * 2; j = j + scale * 8){

				tempol.t.x = buildingspaces.at(i).x + (float) scale / 4;
				tempol.t.y = (float)scale / 10;
				tempol.t.z = (float) j;

				tempol.c = 1;

				tempol.s.x = (float) scale;
				tempol.s.y = (float) scale;
				tempol.s.z = (float) scale;
				tempol.objectIndex = 4;
				objectplacement.push_back(tempol);

				tempol.t.x = buildingspaces.at(i).x + buildingspaces.at(i).width - (float) scale / 4;
				tempol.t.y = (float)scale / 10;
				tempol.t.z = (float)j;

				tempol.c = 1;

				tempol.s.x = (float) scale;
				tempol.s.y = (float) scale;
				tempol.s.z = (float) scale;
				tempol.objectIndex = 4;
				objectplacement.push_back(tempol);
			}

			//lamps x
			for (int j = buildingspaces.at(i).x + scale * 2; j <  buildingspaces.at(i).x + buildingspaces.at(i).width - scale * 2; j = j + scale * 8){

				tempol.t.x = (float) j;
				tempol.t.y = (float) scale / 10;
				tempol.t.z = buildingspaces.at(i).z + (float) scale / 4;

				tempol.c = 1;

				tempol.s.x = (float) scale;
				tempol.s.y = (float) scale;
				tempol.s.z = (float) scale;
				tempol.objectIndex = 4;
				objectplacement.push_back(tempol);

				tempol.t.x = (float) j;
				tempol.t.y = (float) scale / 10;
				tempol.t.z = buildingspaces.at(i).z + buildingspaces.at(i).depth - (float) scale / 4;

				tempol.c = 1;

				tempol.s.x = (float) scale;
				tempol.s.y = (float) scale;
				tempol.s.z = (float) scale;
				tempol.objectIndex = 4;
				objectplacement.push_back(tempol);
			}

			if (buildingspaces.at(i).height <= scale * 10){
				if ((buildingspaces.at(i).width / scale) > 6 && (buildingspaces.at(i).depth / scale) > 6){
					tempol.t.x = buildingspaces.at(i).x + (float) scale* (float) 0.8;
					tempol.t.y = (float) scale / 10;
					tempol.t.z = (float) buildingspaces.at(i).z + scale + (buildingspaces.at(i).depth - scale * 2) / 4;

					tempol.c = 1;

					tempol.s.x = (float) scale;
					tempol.s.y = (float) scale;
					tempol.s.z = (float) scale;
					tempol.objectIndex = 6;
					objectplacement.push_back(tempol);
				}
				else{

				}
			}

			if (buildingspaces.at(i).height > scale * 10){
				//entrance
				tempol.t.x = (float) buildingspaces.at(i).x + buildingspaces.at(i).width / 2;
				tempol.t.y = (float) scale / 10;
				tempol.t.z = (float) buildingspaces.at(i).z + scale * (float) 0.4;

				tempol.c = 1;

				tempol.s.x = (float) scale;
				tempol.s.y = (float) scale;
				tempol.s.z = (float) scale;
				tempol.objectIndex = 2;
				objectplacement.push_back(tempol);
			}

			//car
			if (genRandInt(0, 2) == 0){
				tempol.t.x = (float) buildingspaces.at(i).x + buildingspaces.at(i).width / 4;
				tempol.t.y = 0;
				tempol.t.z = (float)buildingspaces.at(i).z - scale * (float) 0.6;

				tempol.c = 1;

				tempol.s.x = (float) scale;
				tempol.s.y = (float) scale;
				tempol.s.z = (float) scale;
				tempol.objectIndex = 3;
				objectplacement.push_back(tempol);
			}
			if (genRandInt(0, 2) == 0){
				tempol.t.x = (float) buildingspaces.at(i).x - scale * (float) 0.6;;
				tempol.t.y = 0;
				tempol.t.z = (float) buildingspaces.at(i).z + buildingspaces.at(i).depth / 4;

				tempol.c = 1;

				tempol.s.x = (float) scale;
				tempol.s.y = (float) scale;
				tempol.s.z = (float) scale;

				tempol.ra = 90;
				tempol.r.x = 0;
				tempol.r.y = 1;
				tempol.r.z = 0;

				tempol.objectIndex = 3;
				//objectplacement.push_back(tempol);
				tempol.ra = 0;
			}
		}
	}

	for (unsigned i = 0; i < buildingspaces.size(); i++){
		if ((buildingspaces.at(i).width / scale) <= 4 || (buildingspaces.at(i).depth / scale) <= 4){
			if (buildingspaces.at(i).depth > buildingspaces.at(i).width){
				for (int j = buildingspaces.at(i).z + scale; j < buildingspaces.at(i).z + buildingspaces.at(i).depth - scale * 2; j = j + scale * 2){

					tempol.t.x = (float) buildingspaces.at(i).x + buildingspaces.at(i).width / 2;
					tempol.t.y = (float) scale / 200;
					tempol.t.z = (float) j;

					tempol.c = 0;

					tempol.s.x = (float) scale * ((float)genRandInt(50, 100)) / 100;
					tempol.s.y = (float) scale * ((float)genRandInt(50, 100)) / 100;
					tempol.s.z = (float) scale * ((float)genRandInt(50, 100)) / 100;
					tempol.objectIndex = 0;
					objectplacement.push_back(tempol);
				}
			}
			else{
				for (int j = buildingspaces.at(i).x + scale; j < buildingspaces.at(i).x + buildingspaces.at(i).width - scale * 2; j = j + scale * 2){

					tempol.t.x = (float) j;
					tempol.t.y = (float) scale / 200;
					tempol.t.z = (float) buildingspaces.at(i).z + buildingspaces.at(i).depth / 2;

					tempol.c = 0;

					tempol.s.x = scale * ((float)genRandInt(50, 100)) / 100;
					tempol.s.y = scale * ((float)genRandInt(50, 100)) / 100;
					tempol.s.z = scale * ((float)genRandInt(50, 100)) / 100;
					tempol.objectIndex = 0;
					objectplacement.push_back(tempol);
				}
			}
		}

	}
}

void city::genBounds(){
	for (unsigned i = 0; i < buildings.size(); i++){
		for (unsigned j = 0; j < buildings.at(i).getBounds().size(); j++){
			bounds.push_back(buildings.at(i).getBounds().at(j));
		}
	}

	static BBoxCoords tempbb;

	float temp;

	for (unsigned i = 0; i < objectplacement.size(); i++){
		tempbb = objects.at(objectplacement.at(i).objectIndex).getBounds();
		tempbb.maxx = tempbb.maxx * objectplacement.at(i).s.x + objectplacement.at(i).t.x;
		tempbb.minx = tempbb.minx * objectplacement.at(i).s.x + objectplacement.at(i).t.x;
		tempbb.maxz = tempbb.maxz * objectplacement.at(i).s.z + objectplacement.at(i).t.z;
		tempbb.minz = tempbb.minz * objectplacement.at(i).s.z + objectplacement.at(i).t.z;
		bounds.push_back(tempbb);
	}
}


void city::drawCity(int gridsize, int scale){

	std::vector<std::vector<int> > grid;

	std::vector<buildingbox> buildingspaces;

	fillGrid(gridsize, grid);

	genRoads(grid);

	if (gridsize > 6){
		genAlleys(grid);
	}

	calcStartCoord(grid, scale);

	findBuildingSpaces(grid, buildingspaces, scale);

	genBuildings(buildings, buildingspaces, scale);

	placeObjects(objectplacement, buildingspaces, scale);

	genBounds();
}

void city::renderCity(RGB c1, RGB c2, RGB c3){
	point3 tempoint = point3();
	for (unsigned i = 0; i < buildings.size(); i++){
		buildings.at(i).renderBuilding(c1, c2, c3);
	}
	for (unsigned i = 0; i < objectplacement.size(); i++){
		objects.at(objectplacement.at(i).objectIndex).renderWireFrameModel(objectplacement.at(i).c == 1 ? c1 : c3, objectplacement.at(i).t, objectplacement.at(i).s, objectplacement.at(i).ra != 0 ? objectplacement.at(i).r : tempoint, objectplacement.at(i).ra != 0 ? objectplacement.at(i).ra : 0);
	}
}

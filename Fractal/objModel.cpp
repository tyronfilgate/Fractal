#include "objModel.h"
#include "GL/glut.h"

unsigned objModel::starttex = 500;

objModel::objModel(){
	
}

objModel::objModel(std::string filename)
{
	loadOBJ(filename);
}

bool objModel::loadOBJ(std::string filename) {

	bool loadsuccess;

	loadsuccess = objfile.loadFile(filename);

	if (loadsuccess){
		genBounds();
	}

	return loadsuccess;
}

void objModel::setStartTex(unsigned newstart){
	starttex = newstart;
}

void objModel::genBounds() {
	bounds = BBoxCoords();

	for (unsigned i = 0; i < objfile.getNumGroups(); i++) {
		for (unsigned j = 0; j < objfile.getVertices(i).size(); j++) {
			if (objfile.getVertices(i).at(j).x > bounds.maxx){
				bounds.maxx = objfile.getVertices(i).at(j).x;
			}
			else
			if (objfile.getVertices(i).at(j).x < bounds.minx){
				bounds.minx = objfile.getVertices(i).at(j).x;
			}
			if (objfile.getVertices(i).at(j).z > bounds.maxz){
				bounds.maxz = objfile.getVertices(i).at(j).z;
			}
			else
			if (objfile.getVertices(i).at(j).z < bounds.minz){
				bounds.minz = objfile.getVertices(i).at(j).z;
			}
		}
	}
}

const BBoxCoords & objModel::getBounds() const{
	return bounds;
}

void objModel::createDisplayList(const int &listno, point3 translate, point3 scale, point3 rotate, float rotateamount) {
	glNewList(listno, GL_COMPILE);
	renderModel(translate, scale, rotate, rotateamount);
	glEndList();
}

void objModel::createWireFrameDisplayList(const int &listno, RGB c, point3 translate, point3 scale, point3 rotate, float rotateamount){
	glNewList(listno, GL_COMPILE);
	renderWireFrameModel(c, translate, scale, rotate, rotateamount);
	glEndList();
}

void objModel::renderModel(point3 translate, point3 scale, point3 rotate, float rotateamount){
	mtlMaterial temp;
	if (translate.x != 0 || translate.y != 0 || translate.z != 0 || scale.z != 0 || scale.x != 0 || scale.y != 0 || rotate.x != 0 || rotate.y != 0 || rotate.z != 0){
		glPushMatrix();
		if (translate.x != 0 || translate.y != 0 || translate.z != 0){
			glTranslatef(translate.x, translate.y, translate.z);
		}
		if (scale.z != 0 || scale.x != 0 || scale.y != 0){
			glScalef(scale.x, scale.y, scale.z);
		}
		if (rotate.x != 0 || rotate.y != 0 || rotate.z != 0){
			glRotatef(rotateamount, rotate.x, rotate.y, rotate.z);
		}
	}
	for (unsigned i = 0; i < objfile.getNumGroups(); i++) {
		if (objfile.getMaterial(i, temp)){
			if (!temp.map_Kd.empty()){
				if (addTextureID(temp.map_Kd)){
					std::cout << temp.map_Kd << std::endl;
					loadTGATexture(texIDs.find(temp.map_Kd)->second, temp.map_Kd);
				}
			}
		}
		else{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		if (objfile.getNumFace(i) == 3){
			glBegin(GL_TRIANGLES);
		}
		else
		if (objfile.getNumFace(i) == 4){
			glBegin(GL_QUADS);
		}
		else{
			glBegin(GL_POLYGON);
		}
		for (unsigned j = 0; j < objfile.getVertices(i).size(); j++) {
			if (!objfile.getTexCoords(i).empty()) glTexCoord2f(objfile.getTexCoords(i).at(j).x, objfile.getTexCoords(i).at(j).y);
			glVertex3f(objfile.getVertices(i).at(j).x, objfile.getVertices(i).at(j).y, objfile.getVertices(i).at(j).z);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if (translate.x != 0 || translate.y != 0 || translate.z != 0 || scale.z != 0 || scale.x != 0 || scale.y != 0 || rotate.x != 0 || rotate.y != 0 || rotate.z != 0){
		glPopMatrix();
	}
}

void objModel::renderWireFrameModel(RGB c, point3 translate, point3 scale, point3 rotate, float rotateamount) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(0.5);
	if (translate.x != 0 || translate.y != 0 || translate.z != 0 || scale.z != 0 || scale.x != 0 || scale.y != 0 || rotate.x != 0 || rotate.y != 0 || rotate.z != 0){
		glPushMatrix();
		if (translate.x != 0 || translate.y != 0 || translate.z != 0){
			glTranslatef(translate.x, translate.y, translate.z);
		}
		if (scale.z != 0 || scale.x != 0 || scale.y != 0){
			glScalef(scale.x, scale.y, scale.z);
		}
		if (rotate.x != 0 || rotate.y != 0 || rotate.z != 0){
			glRotatef(rotateamount, rotate.x, rotate.y, rotate.z);
		}
	}
	glColor3f(c.r, c.g, c.b);
	for (unsigned i = 0; i < objfile.getNumGroups(); i++) {
		if (objfile.getNumFace(i) == 3){
			glBegin(GL_TRIANGLES);
		}
		else
		if (objfile.getNumFace(i) == 4){
			glBegin(GL_QUADS);
		}
		else{
			glBegin(GL_POLYGON);
		}
		for (unsigned j = 0; j < objfile.getVertices(i).size(); j++) {
			glVertex3f(objfile.getVertices(i).at(j).x, objfile.getVertices(i).at(j).y, objfile.getVertices(i).at(j).z);
		}
		glEnd();
	}
	glPolygonOffset(1, 1);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0, 0, 0);
	for (unsigned i = 0; i < objfile.getNumGroups(); i++) {
		if (objfile.getNumFace(i) == 3){
			glBegin(GL_TRIANGLES);
		}
		else
		if (objfile.getNumFace(i) == 4){
			glBegin(GL_QUADS);
		}
		else{
			glBegin(GL_POLYGON);
		}
		for (unsigned j = 0; j < objfile.getVertices(i).size(); j++) {
			glVertex3f(objfile.getVertices(i).at(j).x, objfile.getVertices(i).at(j).y, objfile.getVertices(i).at(j).z);
		}
		glEnd();
	}
	if (translate.x != 0 || translate.y != 0 || translate.z != 0 || scale.z != 0 || scale.x != 0 || scale.y != 0 || rotate.x != 0 || rotate.y != 0 || rotate.z != 0){
		glPopMatrix();
	}
	glDisable(GL_POLYGON_OFFSET_FILL);
}


bool objModel::addTextureID(std::string newtexture){
	if (texIDs.empty()){
		texIDs[newtexture] = starttex++;
	}
	else{
		if (texIDs.find(newtexture) != texIDs.end()){
			glBindTexture(GL_TEXTURE_2D, texIDs.find(newtexture)->second);
			return false;
		}
		else{
			texIDs[newtexture] = starttex++;
		}
	}

	return true;
}

bool objModel::loadTGATexture(unsigned& texID, std::string filename){

	char temp;
	TGAFile temptga;

	std::ifstream infile(filename.c_str(), std::ios::in | std::ios::binary);
	if (!infile) return false;

	unsigned char TGAheader[18];

	for (unsigned i = 0; i < 18; i++){
		infile.read(&temp, 1);
		TGAheader[i] = temp;
	}

	temptga.pixelsize = (unsigned)TGAheader[16];

	if (temptga.pixelsize != 32 && temptga.pixelsize != 24){
		return false;
	}

	temptga.width = (unsigned)(TGAheader[13] * pow(2, 8) + TGAheader[12]);
	temptga.height = (unsigned)(TGAheader[15] * pow(2, 8) + TGAheader[14]);
	temptga.data = (GLubyte*)malloc(temptga.width * temptga.height * (temptga.pixelsize / 8) * sizeof(GLubyte));

	if (TGAheader[2] == 2){
		for (unsigned i = 0; infile.peek() != EOF && i < temptga.width * temptga.height * (temptga.pixelsize / 8); i++){
			infile.read(&temp, 1);
			temptga.data[i] = (GLubyte)temp;
		}

		GLubyte tempglb;

		for (unsigned i = 0; i < temptga.width * temptga.height * (temptga.pixelsize / 8); (temptga.pixelsize == 24) ? i = i + 3 : i = i + 4){
			tempglb = temptga.data[i];
			temptga.data[i] = temptga.data[i + 2];
			temptga.data[i + 2] = tempglb;
		}

	}
	else{
		unsigned numpixels = temptga.width * temptga.height;
		unsigned currbyte = 0;
		GLubyte temppixel[4];

		do{
			GLubyte chunkheader;

			infile.read(&temp, 1);
			chunkheader = (GLubyte)temp;

			if (chunkheader > 128){
				chunkheader -= 127;

				for (unsigned i = 0; (temptga.pixelsize == 24) ? i < 3 : i < 4; i++){
					infile.read(&temp, 1);
					temppixel[i] = (GLubyte)temp;
				}

				while (chunkheader > 0){
					temptga.data[currbyte++] = temppixel[2];
					temptga.data[currbyte++] = temppixel[1];
					temptga.data[currbyte++] = temppixel[0];

					if (temptga.pixelsize == 32){
						temptga.data[currbyte++] = temppixel[3];
					}

					chunkheader--;
				}
			}
			else{
				chunkheader++;

				while (chunkheader > 0){

					for (unsigned i = 0; (temptga.pixelsize == 24) ? i < 3 : i < 4; i++){
						infile.read(&temp, 1);
						temppixel[i] = (GLubyte)temp;
					}

					temptga.data[currbyte++] = temppixel[2];
					temptga.data[currbyte++] = temppixel[1];
					temptga.data[currbyte++] = temppixel[0];

					if (temptga.pixelsize == 32){
						temptga.data[currbyte++] = temppixel[3];
					}

					chunkheader--;
				}
			}

		} while (currbyte / (temptga.pixelsize / 8) < numpixels);
	}

	infile.close();

	createTexture(texID, temptga);

	return true;
}

void objModel::createTexture(unsigned& texID, TGAFile imagedata){
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, (imagedata.pixelsize == 24) ? GL_RGB : GL_RGBA, imagedata.width, imagedata.height, 0, (imagedata.pixelsize == 24) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imagedata.data);
	freeImage(imagedata);
}

void objModel::freeImage(TGAFile imagedata){
	free(imagedata.data);
	imagedata.data = NULL;
}

void objModel::clear(){
	objfile.clear();
}
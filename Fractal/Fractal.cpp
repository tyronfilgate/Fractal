//  Fractal.cpp
//
//  Implementation file for Fractal Class
//
//  Tyron Filgate, August 2017
//--------------------------------------------------------------------------------------

#include <GL/glut.h>

#include "Fractal.h"

#define FRACTAL_EXIT				231
#define FRACTAL_WELCOME				233
#define FRACTAL_INSTRUCTIONS		234

// TEXTURE IMAGE AXISES
#define XY		0
#define XZ		1
#define YZ		2
#define YZ_FLIP 3
#define XY_FLIP 4

//Initalise static Members to NULL Equivalent
int Fractal::state = 0;
void(*Fractal::shayDisplayFunc)() = NULL;
Fractal* Fractal::frac = NULL;
void(*Fractal::shayFrameCountFunction)() = NULL;


//--------------------------------------------------------------------------------------
// Set initial values
//--------------------------------------------------------------------------------------
Fractal::Fractal()
{
	GLdouble* stepIncrement = NULL;
	GLdouble* angleIncrement = NULL;
	int* screenWidth = 0;
	int* screenHeight = 0;
}

void Fractal::DrawPrompts(){
	tp->CreateDisplayList(XY, 1087, 512, 512, 0, 10.0, 0.0, 1, 1);
	tp->CreateDisplayList(XY, 1088, 512, 512, 0, 10.0, 0.0, 1, 1);
	tp->CreateDisplayList(XY, 1089, 512, 512, 0, 10.0, 0.0, 1, 1);
}

void Fractal::setState(int newstate){
	state = newstate; 
};

int Fractal::getState(){
	return state; 
};

//--------------------------------------------------------------------------------------
// Set required objects
//--------------------------------------------------------------------------------------
void Fractal::SetContents(TexturedPolygons* tp_value, Camera* cam_value, void(*newShayDisplayFunc)(), Fractal* newfrac, void(*newshayFrameCountFunction)(), GLdouble* newstepIncrement, GLdouble* newangleIncrement, int* newscreenWidth, int* newscreenHeight)
{
	tp = tp_value;
	cam = cam_value;
	shayDisplayFunc = newShayDisplayFunc;
	frac = newfrac;
	shayFrameCountFunction = newshayFrameCountFunction;
	stepIncrement = newstepIncrement;
	angleIncrement = newangleIncrement;
	screenHeight = newscreenHeight;
	screenWidth = newscreenWidth;
}

void Fractal::DisplayWelcome(){
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, *screenWidth, 0, *screenHeight);
	glScalef(1, -1, 1);

	glTranslated(*screenWidth / 2 - 256.0, -*screenHeight / 2 - 256.0, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(FRACTAL_WELCOME));
	
	glCallList(1087);

	glBindTexture(GL_TEXTURE_2D, 0);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Fractal::DisplayInstructions(){
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, *screenWidth, 0, *screenHeight);
	glScalef(1, -1, 1);

	glTranslated(*screenWidth / 2 - 256.0, -*screenHeight / 2 - 256.0, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(FRACTAL_INSTRUCTIONS));

	glCallList(1088);

	glBindTexture(GL_TEXTURE_2D, 0);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Fractal::DisplayExit(){
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, *screenWidth, 0, *screenHeight);
	glScalef(1, -1, 1);

	glTranslated(*screenWidth / 2 - 256.0, -*screenHeight / 2 - 256.0, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(FRACTAL_EXIT));

	glCallList(1089);

	glBindTexture(GL_TEXTURE_2D, 0);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void Fractal::GameState(){
	switch (state){
		case 0:
			shayDisplayFunc();
			break;
		//First vist to fractal; need to init coords & other stuff
		case 1:
			frac->initFractal();
			break;
		//game
		default:
			frac->FractalDisplay();
			break;
	}	
	
}

void Fractal::InitaliseWorld(){
	w.genWorld(6, 1200);
	w.createDisplayList(1090);
}

int Fractal::getNumBoundingBoxes(){
	return w.getBounds().size();
}

void Fractal::setBounds(unsigned startBBox){
	for (unsigned i = startBBox, indexcount = 0; i  < w.getBounds().size() + startBBox; i++, indexcount++){
		cam->SetAABBMaxX(i, w.getBounds().at(indexcount).maxx);
		cam->SetAABBMinX(i, w.getBounds().at(indexcount).minx);
		cam->SetAABBMaxZ(i, w.getBounds().at(indexcount).maxz);
		cam->SetAABBMinZ(i, w.getBounds().at(indexcount).minz);
		cam->SetAABBMaxY(i, 10000);
		cam->SetAABBMinY(i, 0);
	}
}

void Fractal::initFractal(){
	cam->Position(w.getStartCoord().x, w.getStartCoord().y, w.getStartCoord().z, 90.0);
	cam->SetRotateSpeed(0.0f);
	cam->SetMoveSpeed(0.0f);
	glClearColor(0, 0, 0, 1);
	state = 2;
}

//--------------------------------------------------------------------------------------
// Fractal Game World Display Function
//--------------------------------------------------------------------------------------
void Fractal::FractalDisplay()
{
	// check for movement
	cam->CheckCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		shayFrameCountFunction();
		if (state == 4){
			cam->SetMoveSpeed(*stepIncrement);
			cam->SetRotateSpeed(*angleIncrement);
		}
		//Welcome Screen
		if (state == 2){
			DisplayWelcome();
		}

		//instructions
		if (state == 3){
			DisplayInstructions();
		}

		//Exit Splash Screen
		if (state == 5){
			DisplayExit();
		}

		glCallList(1090);
		
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// clear buffers
	glFlush();
	glutSwapBuffers();
}
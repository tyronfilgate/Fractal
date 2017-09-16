//  Fractal.cpp
//
//  Implementation file for Fractal Class
//
//  Tyron Filgate, August 2017
//--------------------------------------------------------------------------------------

#include <GL/glut.h>

#include "Fractal.h"

#define FRACTAL_EXIT				231
#define FRACTAL_WELCOME				232
#define FRACTAL_INSTRUCTIONS		233

//--------------------------------------------------------------------------------------
// Set initial values
//--------------------------------------------------------------------------------------
Fractal::Fractal()
{
	fractalEntered = false;
	welcomeDisplay = false;
	exitDisplay = false;
	instructionDisplay = false;
}

//--------------------------------------------------------------------------------------
// Set required objects
//--------------------------------------------------------------------------------------
void Fractal::SetContents(TexturedPolygons* tp_value, Camera* cam_value)
{
	tp = tp_value;
	cam = cam_value;

}

//--------------------------------------------------------------------------------------
// Fractal Game World Display Function
//--------------------------------------------------------------------------------------
void Fractal::FractalDisplay()
{
	cam->Position(0.0, 0.0, 0.0, 180.0);
	cam->SetMoveSpeed(0);
	cam->SetRotateSpeed(0);

	// check for movement
	cam->CheckCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();

		//Displays FRACTAL Welcome Splash
		if (IsWelcomeDisplayed()) cam->DisplayWelcomeScreen(width, height, 1, tp->GetTexture(FRACTAL_WELCOME));

		//Displays Bonzer Exit Splash
		if (IsExitDisplayed()) cam->DisplayWelcomeScreen(width, height, 0, tp->GetTexture(FRACTAL_EXIT));

		//Displays the Instruction Screen for FRACTAL
		if (IsExitDisplayed()) cam->DisplayWelcomeScreen(width, height, 0, tp->GetTexture(FRACTAL_INSTRUCTIONS));
		
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// clear buffers
	glFlush();
	glutSwapBuffers();
}
//  Fractal.h
//  Header file for the Fractal class
//	The code used for the Fractal Game.
//
//  Tyron Filgate, August 2017
//--------------------------------------------------------------------------------------

#include "texturedPolygons.h"
#include "camera.h"
#include "objModel.h"

class Fractal
{
public:

	Fractal();	//Constructor
	void FractalDisplay(); 	//Calls the display function of FRACTAL
	void SetContents(TexturedPolygons* tp_value, Camera* cam_value);	//Camera and Texture objects from Shay's World.
	void SetWindowAspects(int w, int h) { width = w; height = h; };	//Sets the width and height values in this class on reshape

	bool IsFractalEntered() { return fractalEntered; };
	bool IsWelcomeDisplayed() { return welcomeDisplay; };
	bool IsExitDisplayed() { return exitDisplay; };
	bool IsInstructionDisplayed() { return instructionDisplay; };

	void EnterFractal(bool value) { fractalEntered = value };
	void SetWelcomeDisplayed(bool value) { welcomeDisplay = value; };
	void SetExitDisplayed(bool value) { exitDisplay = value; };
	void SetInstructionDisplayed(bool value) { instructionDisplay = value; };

private:

	int width;
	int height;

	bool fractalEntered;
	bool welcomeDisplay;
	bool exitDisplay;
	bool instructionDisplay;

	TexturedPolygons* tp;
	Camera* cam;
	objModel ob;

};
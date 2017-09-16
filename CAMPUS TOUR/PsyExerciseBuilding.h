//  PsyExerciseBuilding.h
//  Header file for the Psychology and Exercise Building class
//	Allows the world to display the Psychology and Exercise Building.
//
//  Tyron Filgate, August 2017
//--------------------------------------------------------------------------------------

#include "texturedPolygons.h"
#include "camera.h"
#include "objModel.h"

class PsyExerciseBuilding
{
public:

	PsyExerciseBuilding();
	void SetContents(TexturedPolygons* tp_value, Camera* cam_value);

	void DrawPEB();
	void DisplayPEB();

	void SetPEBCollision();
	void SetPEBPlains();

private:

	void DrawDoorway();
	void DrawEntranceRoom();
	void DrawStairsDown();
	void DrawStairsUp();
	void DrawLevelZero();
	void DrawLevelOneHalf();
	void DrawStairwell();
	void DrawDoorsandWindows();
	void DrawStairsUpLvl1();
	void DrawObjObjects();

	void DisplayDoorway();
	void DisplayEntranceRoom();
	void DisplayStairsDown();
	void DisplayStairsUp();
	void DisplayLevelZero();
	void DisplayLevelOneHalf();
	void DisplayStairwell();
	void DisplayDoorsandWindows();
	void DisplayStarsUpLvl1();
	void DisplayObjObjects();

	TexturedPolygons* tp;
	Camera* cam;
	objModel ob;
};
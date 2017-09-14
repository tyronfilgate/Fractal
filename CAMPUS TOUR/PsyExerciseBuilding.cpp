//  PsyExerciseBuilding.cpp
//
//  Implementation file for Psychology and Exercise Building Class
//
//  Tyron Filgate, August 2017
//--------------------------------------------------------------------------------------

#include "PsyExerciseBuilding.h"

//PLAIN TYPES
#define FLAT_PLAIN	0

// TEXTURE IMAGE AXISES
#define XY		0
#define XZ		1
#define YZ		2
#define YZ_FLIP 3
#define XY_FLIP 4

// TEXTURES
#define WALL_BRICK_YZ				15
#define WALL_BRICK_XY				16
#define	WALL_BRICK_USD_YZ			20
#define	STEP_PAVING_1				123
#define	STEP_EDGE					124


//--------------------------------------------------------------------------------------
// Set initial values
//--------------------------------------------------------------------------------------
PsyExerciseBuilding::PsyExerciseBuilding()
{
}

//--------------------------------------------------------------------------------------
// Set TP object
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::SetContents(TexturedPolygons* tp_value, Camera* cam_value)
{
	tp = tp_value;
	cam = cam_value;

}

//--------------------------------------------------------------------------------------
// Draws the Psychology and Exercise Building
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DrawPEB()
{
	DrawDoorway();
	DrawEntranceRoom();
	DrawStairsDown();
	DrawStairsUp();
}

//--------------------------------------------------------------------------------------
// Displays the Psychology and Exercise Building
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DisplayPEB()
{
	DisplayDoorway();
	DisplayEntranceRoom();
	DisplayStairsDown();
	DisplayStairsUp();
}

//--------------------------------------------------------------------------------------
// Draws the Psychology and Exercise Building doorway
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DrawDoorway()
{
	//Entrance
	tp->CreateDisplayList(XY, 1000, 128.0, 128.0, 2108.0, 10000.0, 28000.0, 3.92, 7.0); //Left Wall / Translated for Right Wall
	tp->CreateDisplayList(XZ, 1001, 128.0, 128.0, 2108.0, 10896.0, 26640.0, 3.92, 10.7); //Top Wall
	tp->CreateDisplayList(YZ, 1002, 128.0, 128.0, 2108.0, 10000.0, 26640.0, 7.0, 2.5); //Right door wall section / Translated for Left door wall section

	//Entrance Door
	tp->CreateDisplayList(YZ, 1003, 128.0, 128.0, 2109.0, 10000.0, 27320.0, 6.5, 3.125); //Left
	tp->CreateDisplayList(YZ, 1004, 128.0, 128.0, 2110.0, 10000.0, 26920.0, 6.5, 3.125); //Right

}

//--------------------------------------------------------------------------------------
// Draws the Psychology and Exercise Building entrance room
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DrawEntranceRoom()
{
	//ECL Side Wall
	tp->CreateDisplayList(XY, 1005, 128.0, 128.0, 0.0, 10000.0, 28500.0, 16.46, 6.5);	//Bottom Left
	tp->CreateDisplayList(XY, 1006, 128.0, 128.0, -1250.0, 10000.0, 28500.0, 5.0, 6.5); //Bottom Right
	tp->CreateDisplayList(XY, 1007, 128.0, 128.0, -1250.0, 10832.0, 28500.0, 26.23, 3.5); //Top

	//Rear Wall
	tp->CreateDisplayList(YZ, 1008, 128.0, 128.0, -1250.0, 10000.0, 26640.0, 10.0, 14.53); //Left

	//Corridor Door Walls
	tp->CreateDisplayList(XY, 1009, 128.0, 128.0, -1506.0, 10000.0, 26640.0, 2.0, 10.0); //Left / Translate for right.
	tp->CreateDisplayList(YZ, 1010, 128.0, 128.0, -1506.0, 10832.0, 25940.0, 3.5, 5.46); //Top

	//Tavern Wall
	tp->CreateDisplayList(XY, 1011, 128.0, 128.0, -950.0, 10000.0, 25940.0, 6.0, 6.5); //Between Doors
	tp->CreateDisplayList(XY, 1012, 128.0, 128.0, 118.0, 10000.0, 25940.0, 2.0, 6.5); //Between Office Door and Reception
	tp->CreateDisplayList(XY, 1013, 128.0, 128.0, -1250.0, 10832.0, 25940.0, 26.23, 3.5); //Top

	//Entrance Wall
	tp->CreateDisplayList(YZ, 1014, 128.0, 128.0, 2108.0, 10000.0, 25940.0, 10.0, 5.46); //Left
	tp->CreateDisplayList(YZ, 1015, 128.0, 128.0, 2108.0, 10000.0, 28000.0, 10.0, 3.9); //Right
	tp->CreateDisplayList(YZ, 1016, 128.0, 128.0, 2108.0, 10896.0, 26640.0, 3.0, 10.625); //Top

	//Ceiling
	tp->CreateDisplayList(XZ, 1017, 128.0, 128.0, -1506.0, 11280.0, 25940.0, 28.23, 20);

	//Floor
	tp->CreateDisplayList(XZ, 1018, 128.0, 128.0, -1506.0, 10000.0, 25940.0, 28.23, 20);
}

//--------------------------------------------------------------------------------------
// Draws the Psychology and Exercise Building stairs to level 0
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DrawStairsDown()
{
	GLdouble step = 10000.0;
	GLdouble stepLength = 25250.0;

	for (int i = 1018; i < 1025; i++) //Stairs Down - 1018-1024 Upright / 1025-1032 Flat
	{
		tp->CreateDisplayList(XZ, i, 1024.0, 512.0, -1506.0, step, stepLength, 0.646, 0.195);
		tp->CreateDisplayList(XY, i + 7, 64.0, 64.0, -1506.0, step - 64.0, stepLength, 10.34, 1.0);
		step -= 64.0;
		stepLength -= 100.0;
	}

}

//--------------------------------------------------------------------------------------
// Draws the Psychology and Exercise Building stairs to level 1.5
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DrawStairsUp()
{
	GLdouble step = 10000.0;
	GLdouble stepLength = 25250.0;
	
	for (int i = 1033; i < 1040; i++) //Stairs Up - 1033-1039 Upright / 1040-1046 Flat
	{
		tp->CreateDisplayList(XZ, i, 1024.0, 512.0, -844.0, step, stepLength - 100.0, 0.646, 0.195);
		tp->CreateDisplayList(XY, i + 7, 64.0, 64.0, -844.0, step, stepLength - 100, 10.34, 1.0);
		step += 64.0;
		stepLength -= 100.0;
	}

}

//--------------------------------------------------------------------------------------
// Displays the Psychology and Exercise Building doorway
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DisplayDoorway()
{
	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WALL_BRICK_XY)); 
	glCallList(1000);

	glPushMatrix();
		glTranslated(0.0, 0.0, -1360.0);
		glCallList(1000);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WALL_BRICK_USD_YZ));
	glCallList(1001);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WALL_BRICK_YZ));
	glCallList(1002);

	glPushMatrix();
		glTranslated(0.0, 0.0, 1040.0);
		glCallList(1002);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(160)); //TODO: Add left door texture
	glCallList(1003);
	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(161)); //TODO: Add right door texture
	glCallList(1004);

}

//--------------------------------------------------------------------------------------
// Displays the Psychology and Exercise Building entrance room
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DisplayEntranceRoom()
{
	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WALL_BRICK_XY));
	glCallList(1005);
	glCallList(1006);
	glCallList(1007);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WALL_BRICK_YZ));
	glCallList(1008);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WALL_BRICK_XY));
	glCallList(1009);

	glPushMatrix();
		glTranslated(0.0, 0.0, -700.0);
		glCallList(1009);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WALL_BRICK_YZ));
	glCallList(1010);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WALL_BRICK_XY));
	glCallList(1011);
	glCallList(1012);

	glPushMatrix();
		glTranslated(1734.0, 0.0, 0.0);
		glCallList(1012);
	glPopMatrix();

	glCallList(1013);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WALL_BRICK_YZ));
	glCallList(1014);
	glCallList(1015);
	glCallList(1016);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(97)); //TODO: Add ceiling texture
	glCallList(1017);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(126)); //TODO: Add floor texture
	glCallList(1018);

}

//--------------------------------------------------------------------------------------
// Displays the Psychology and Exercise Building stairs to level 0
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DisplayStairsDown()
{
	int i;

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(STEP_PAVING_1));
	for (i = 1018; i < 1025; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(STEP_EDGE));
	for (i = 1025; i < 1033; i++) glCallList(i);

}

//--------------------------------------------------------------------------------------
// Displays the Psychology and Exercise Building stairs to level 1.5
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DisplayStairsUp()
{
	int i;

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(STEP_PAVING_1));
	for (i = 1033; i < 1040; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(STEP_EDGE));
	for (i = 1040; i < 1047; i++) glCallList(i);

}

//--------------------------------------------------------------------------------------
// Sets the Psychology and Exercise Building bounding boxes for collision
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::SetPEBCollision()
{
	// Canteen block - Library End
	cam->SetAABBMaxX(12, 2608.0);
	cam->SetAABBMinX(12, 2108.0);
	cam->SetAABBMaxZ(12, 49046.0);
	cam->SetAABBMinZ(12, 28000.0);
	
	// Canteen block - Tavern End
	cam->SetAABBMaxX(17, 2608.0);
	cam->SetAABBMinX(17, 2108.0);
	cam->SetAABBMaxZ(17, 26550.0);
	cam->SetAABBMinZ(17, 0.0);

	// Entrance Room Library side
	cam->SetAABBMaxX(18, 2108.0);
	cam->SetAABBMinX(18, -3000.0);
	cam->SetAABBMaxZ(18, 49046.0);
	cam->SetAABBMinZ(18, 28500.0);

	// Entrance Room Tavern side
	cam->SetAABBMaxX(19, 2108.0);
	cam->SetAABBMinX(19, -182);
	cam->SetAABBMaxZ(19, 25940.0);
	cam->SetAABBMinZ(19, 0.0);

	// Entrance Room Student Village side
	cam->SetAABBMaxX(20, -1506.0);
	cam->SetAABBMinX(20, -3000.0);
	cam->SetAABBMaxZ(20, 49046.0);
	cam->SetAABBMinZ(20, 0.0);
	
}

//--------------------------------------------------------------------------------------
// Sets the Psychology and Exercise Building plains for movement
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::SetPEBPlains()
{
	int i;

	cam->SetPlains(FLAT_PLAIN, -1550.0, 36000.0, 10450.0, 10450.0, 25250.0, 45610.0); // ENDS AT PsyEx Stairwell

	GLdouble step = 10450.0;
	GLdouble stepLength = 25250.0;
	
	// Stairs to level 0
	for (i = 0; i < 7; i++)
	{
		cam->SetPlains(FLAT_PLAIN, -1506.0, -844, step, step, stepLength, stepLength - 100);
		step -= 64.0;
		stepLength -= 100.0;
	}

	// Stairs to level 1.5
	for (i = 0; i < 7; i++)
	{
		cam->SetPlains(FLAT_PLAIN, -844, -182, step, step, stepLength, stepLength - 100);
		step += 64.0;
		stepLength -= 100.0;
	}

}

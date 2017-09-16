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
#define WHITE_WALL					223
#define CLEAR_FRAME					224
#define BRICK_STAIRWELL				225
#define DOOR_LEFT_PSY				226
#define DOOR_BACK_PSY				227
#define DOOR_RIGHT_PSY				228
#define SHELF_RIGHT_PSY				229
#define ROOF_PSY					230

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
	DrawLevelZero();
	DrawLevelOneHalf();
	DrawStairwell();
	DrawStairsUpLvl1();
	DrawObjObjects();
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
	DisplayStairsUp();
	DisplayLevelZero();
	DisplayLevelOneHalf();
	DisplayStairwell();
	DisplayStarsUpLvl1();
	DisplayObjObjects();
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

}

void  PsyExerciseBuilding::DrawObjObjects(){
	ob.loadOBJ("./Models/stairwell.obj");
	ob.createDisplayList(1080, { -800, 9300, 24700.0 }, { 280, 250, 180 });
	ob.clear();
}

void PsyExerciseBuilding::DisplayObjObjects(){
	//Stair Railing
	glCallList(1080);
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

	//Door on ECL Side		
	tp->CreateDisplayList(XY, 1081, 1024, 1024.0, -663.0, 10000.0, 28497.0, 0.65, 1);

	//Door at rear
	tp->CreateDisplayList(YZ, 1082, 1024, 1024, -1500.0, 10000.0, 25940.0, 1, 0.7); 

	//Door at right
	tp->CreateDisplayList(XY, 1083, 456, 832, -200.0, 10000.0, 25945.0, 1, 1); 

	//Shelf at right
	tp->CreateDisplayList(XY, 1084, 2158, 834, 373.0, 10000.0, 25945.0, 0.7, 1); 

	tp->CreateDisplayList(YZ, 1008, 128.0, 128.0, -1250.0, 10000.0, 26640.0, 10.0, 14.53); //Left

	//Corridor Door Walls
	tp->CreateDisplayList(XY, 1009, 128.0, 128.0, -1506.0, 10000.0, 26640.0, 2.0, 15.0); //Left / Translate for right.
	tp->CreateDisplayList(YZ, 1010, 128.0, 128.0, -1506.0, 10832.0, 25940.0, 3.5, 7.0); //Top

	//Tavern Wall
	tp->CreateDisplayList(XY, 1011, 128.0, 128.0, -950.0, 9232.0, 25940.0, 6.0, 12.5); //Between Doors
	tp->CreateDisplayList(XY, 1012, 128.0, 128.0, 118.0, 10000.0, 25940.0, 2.0, 6.5); //Between Office Door and Reception
	tp->CreateDisplayList(XY, 1013, 128.0, 128.0, -1250.0, 10832.0, 25940.0, 26.23, 7.0); //Top

	tp->CreateDisplayList(XY, 1100, 512, 256, -800, 10500, 25943.0, 1, 1); //Clear Screen Thing

	//Entrance Wall
	tp->CreateDisplayList(YZ, 1014, 128.0, 128.0, 2108.0, 10000.0, 25940.0, 10.0, 5.46); //Left
	tp->CreateDisplayList(YZ, 1015, 128.0, 128.0, 2108.0, 10000.0, 28000.0, 10.0, 3.9); //Right
	tp->CreateDisplayList(YZ, 1016, 128.0, 128.0, 2108.0, 10896.0, 26640.0, 3.0, 10.625); //Top

	//Ceiling
	tp->CreateDisplayList(XZ, 1017, 128.0, 128.0, -1506.0, 11280.0, 25940.0, 28.23, 20);

	//Floor
	tp->CreateDisplayList(XZ, 1064, 128.0, 128.0, -1506.0, 10000.0, 25940.0, 28.23, 20);
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
		tp->CreateDisplayList(XZ, i, 1024.0, 512.0, -1506.0, step, stepLength, 0.546, 0.195);
		tp->CreateDisplayList(XY, i + 7, 64.0, 64.0, -1506.0, step - 64.0, stepLength, 8.7, 1.0);
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
		tp->CreateDisplayList(XZ, i, 1024.0, 512.0, -700.0, step, stepLength - 100.0, 0.546, 0.195);
		tp->CreateDisplayList(XY, i + 7, 64.0, 64.0, -704.0, step, stepLength - 100.0, 8, 1.0);
		step += 64.0;
		stepLength -= 100.0;
	}

}

//--------------------------------------------------------------------------------------
// Draws the Psychology and Exercise Building stairs to level 1
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DrawStairsUpLvl1()
{
	GLdouble step = 10900.0;
	GLdouble stepLength = 25250.0;
	
	int i;

	for (i = 1065; i < 1072; i++)
	{
		tp->CreateDisplayList(XZ, i, 1024.0, 512.0, -1506.0, step, stepLength - 100.0, 0.546, 0.195);
		tp->CreateDisplayList(XY, i + 7, 64.0, 64.0, -1506.0, step - 64, stepLength - 100.0, 8.7, 1.0);
		step -= 64.0;
		stepLength -= 100.0;
	}
}

//--------------------------------------------------------------------------------------
// Draws the Psychology and Exercise Building Level 0
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DrawLevelZero()
{
	//Floor
	tp->CreateDisplayList(XZ, 1047, 128.0, 128.0, -1506.0, 9550.0, 23860.0, 10.34, 16.25);

}

//--------------------------------------------------------------------------------------
// Draws the Psychology and Exercise Building Level 1.5/2
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DrawLevelOneHalf()
{
	//Floor
	tp->CreateDisplayList(XZ, 1048, 128.0, 128.0, -1506.0, 10450.0, 23860.0, 10.34, 5.4);

	//Ceiling
	tp->CreateDisplayList(XZ, 1049, 128.0, 128.0, -1506.0, 11349.0, 23860.0, 10.34, 16.25);

}

//--------------------------------------------------------------------------------------
// Draws the Psychology and Exercise Building Stairwell
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DrawStairwell()
{
	//Bush Court Wall
	tp->CreateDisplayList(YZ, 1050, 128.0, 128.0, -182, 9550.0, 23860.0, 3.52, 16.25);		//Level 0
	tp->CreateDisplayList(YZ, 1051, 128.0, 128.0, -182, 10000.0, 23860.0, 6.5, 12.91);		//Level 1 Left
	tp->CreateDisplayList(YZ, 1052, 128.0, 128.0, -182, 10000.0, 25812.0, 6.5, 1.0);		//Level 1 Right
	tp->CreateDisplayList(YZ, 1053, 128.0, 128.0, -182, 10832.0, 23860.0, 4.05, 16.25);		//Level 1 Top

	//Tavern Wall
	tp->CreateDisplayList(XY, 1054, 128.0, 128.0, -1506.0, 9550.0, 23860.0, 10.34, 7.03);	//Level 0
	tp->CreateDisplayList(XY, 1055, 128.0, 128.0, -1506.0, 10450.0, 23860.0, 1.0, 6.5);		//Level 1.5 Left
	tp->CreateDisplayList(XY, 1056, 128.0, 128.0, -1078.0, 10450.0, 23860.0, 7.0, 6.5);		//Level 1.5 Right
	tp->CreateDisplayList(XY, 1057, 128.0, 128.0, -1506.0, 11282.0, 23860.0, 10.34, 0.53);	//Level 1.5 Top

	//Student Village Wall
	tp->CreateDisplayList(YZ, 1058, 128.0, 128.0, -1506.0, 9550.0, 24360.0, 6.5, 12.34);	//Level 0 Left
	tp->CreateDisplayList(YZ, 1059, 128.0, 128.0, -1506.0, 9550.0, 23860.0, 6.5, 1.56);		//Level 0 Right
	tp->CreateDisplayList(YZ, 1060, 128.0, 128.0, -1506.0, 10382.0, 23860.0, 3.53, 16.25);	//Level 0 Top

	tp->CreateDisplayList(YZ, 1061, 128.0, 128.0, -1506.0, 10834.0, 24360.0, 3.5, 12.34);	//Level 1.5 Left
	tp->CreateDisplayList(YZ, 1062, 128.0, 128.0, -1506.0, 10834.0, 23860.0, 3.5, 1.56);	//Level 1.5 Right
	tp->CreateDisplayList(YZ, 1063, 128.0, 128.0, -1506.0, 11282.0, 23860.0, 0.53, 16.25);	//Level 1.5 Top

	//Stairs Entrance Floor
	tp->CreateDisplayList(XZ, 1105, 128.0, 128.0, -1506.0, 10001.0, 25250.0, 10.34, 5.4);
}

//--------------------------------------------------------------------------------------
// Draws the Psychology and Exercise Building Doors and Windows
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DrawDoorsandWindows()
{
	//Entrance Door
	tp->CreateDisplayList(YZ, 1003, 128.0, 128.0, 2109.0, 10000.0, 27320.0, 6.5, 3.125); //Left
	tp->CreateDisplayList(YZ, 1004, 128.0, 128.0, 2110.0, 10000.0, 26920.0, 6.5, 3.125); //Right

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

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	glPushMatrix();
		glTranslated(-1, 0.0, 0);
		glCallList(1002);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WALL_BRICK_YZ));
	glPushMatrix();
		glTranslated(0.0, 0.0, 1040.0);
		glCallList(1002);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	glPushMatrix();
		glTranslated(-1, 0.0, 1040.0);
		glCallList(1002);
	glPopMatrix();
}

//--------------------------------------------------------------------------------------
// Displays the Psychology and Exercise Building entrance room
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DisplayEntranceRoom()
{
	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	glCallList(1005);
	glCallList(1006);
	glCallList(1007);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(DOOR_LEFT_PSY));
	glCallList(1081);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(DOOR_BACK_PSY));
	glCallList(1082);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(DOOR_RIGHT_PSY));
	glCallList(1083);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(SHELF_RIGHT_PSY));
	glCallList(1084);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	glCallList(1008);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	glCallList(1009);

	glPushMatrix();
		glTranslated(0.0, 0.0, -700.0);
		glCallList(1009);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	glCallList(1010);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	glCallList(1011);
	glCallList(1012);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(CLEAR_FRAME));
	glCallList(1100);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	glPushMatrix();
		glTranslated(1734.0, 0.0, 0.0);
		glCallList(1012);
	glPopMatrix();

	glCallList(1013);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	glCallList(1014);
	glCallList(1015);
	glCallList(1016);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(ROOF_PSY));
	glCallList(1017);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(126)); //TODO: Add floor texture
	glCallList(1064);

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

void PsyExerciseBuilding::DisplayStarsUpLvl1(){
	int i;

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(STEP_PAVING_1));
	for (i = 1065; i < 1072; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(STEP_EDGE));
	for (i = 1072; i < 1079; i++) glCallList(i);
}

//--------------------------------------------------------------------------------------
// Displays the Psychology and Exercise Building Level 0
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DisplayLevelZero()
{
	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(BRICK_STAIRWELL));	
	glCallList(1047);
}

//--------------------------------------------------------------------------------------
// Displays the Psychology and Exercise Building Level 1.5/2
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DisplayLevelOneHalf()
{
	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(BRICK_STAIRWELL));
	glCallList(1048);
	glCallList(1049);
}

//--------------------------------------------------------------------------------------
// Displays the Psychology and Exercise Building Stairwell
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DisplayStairwell()
{
	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	for (int i = 1050; i < 1054; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	for (int i = 1054; i < 1058; i++) glCallList(i);

	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(WHITE_WALL));
	for (int i = 1058; i < 1064; i++) glCallList(i);

	//Stairs Entrance floor
	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(BRICK_STAIRWELL));
	glCallList(1105);
}

//--------------------------------------------------------------------------------------
// Displays the Psychology and Exercise Building Doors and Windows
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::DisplayDoorsandWindows()
{
	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(160)); //TODO: Add left door texture
	glCallList(1003);
	glBindTexture(GL_TEXTURE_2D, tp->GetTexture(161)); //TODO: Add right door texture
	glCallList(1004);


}

//--------------------------------------------------------------------------------------
// Sets the Psychology and Exercise Building bounding boxes for collision
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::SetPEBCollision()
{
	// Canteen block - Library End
	cam->SetAABBMaxX(12, 2608.0);
	cam->SetAABBMinX(12, 2108.0);
	cam->SetAABBMinY(12, 0.0);
	cam->SetAABBMaxY(12, 30000.0);
	cam->SetAABBMaxZ(12, 49046.0);
	cam->SetAABBMinZ(12, 28000.0);
	
	// Canteen block - Tavern End
	cam->SetAABBMaxX(17, 2608.0);
	cam->SetAABBMinX(17, 2108.0);
	cam->SetAABBMinY(17, 0.0);
	cam->SetAABBMaxY(17, 30000.0);
	cam->SetAABBMaxZ(17, 26550.0);
	cam->SetAABBMinZ(17, 0.0);

	// Entrance Room Library side
	cam->SetAABBMaxX(18, 2108.0);
	cam->SetAABBMinX(18, -3000.0);
	cam->SetAABBMinY(18, 0.0);
	cam->SetAABBMaxY(18, 30000.0);
	cam->SetAABBMaxZ(18, 49046.0);
	cam->SetAABBMinZ(18, 28500.0);

	// Entrance Room Tavern side + Stairwell Bush court side
	cam->SetAABBMaxX(19, 2108.0);
	cam->SetAABBMinX(19, -182);
	cam->SetAABBMinY(19, 0.0);
	cam->SetAABBMaxY(19, 30000.0);
	cam->SetAABBMaxZ(19, 25940.0);
	cam->SetAABBMinZ(19, 0.0);

	// Entrance Room/Stairwell Student Village side
	cam->SetAABBMaxX(20, -1506.0);
	cam->SetAABBMinX(20, -3000.0);
	cam->SetAABBMinY(20, 0.0);
	cam->SetAABBMaxY(20, 30000.0);
	cam->SetAABBMaxZ(20, 49046.0);
	cam->SetAABBMinZ(20, 0.0);
	/*
	// Stairwell 2nd floor
	cam->SetAABBMaxX(21, -844);
	cam->SetAABBMinX(21, -1506.0);
	cam->SetAABBMinY(21, 10500.0);
	cam->SetAABBMaxY(21, 30000.0);
	cam->SetAABBMaxZ(21, 25250.0);
	cam->SetAABBMinZ(21, 23860.0);
	*/
	// Stairwell Tavern Side
	cam->SetAABBMaxX(22, 2000.0);
	cam->SetAABBMinX(22, -3000.0);
	cam->SetAABBMinY(22, 0.0);
	cam->SetAABBMaxY(22, 30000.0);
	cam->SetAABBMaxZ(22, 23860.0);
	cam->SetAABBMinZ(22, 0.0);

	// Level 0 Understairs
	cam->SetAABBMaxX(23, -182.0);
	cam->SetAABBMinX(23, -844.0);
	cam->SetAABBMinY(23, 0.0);
	cam->SetAABBMaxY(23, 10400.0);
	cam->SetAABBMaxZ(23, 25250.0);
	cam->SetAABBMinZ(23, 0.0);

	//Interior Wall 1
	cam->SetAABBMaxX(24, -150);
	cam->SetAABBMinX(24, -1000);
	cam->SetAABBMinY(24, 0.0);
	cam->SetAABBMaxY(24, 30000.0);
	cam->SetAABBMaxZ(24, 26000);
	cam->SetAABBMinZ(24, 25900);
}

//--------------------------------------------------------------------------------------
// Sets the Psychology and Exercise Building plains for movement
//--------------------------------------------------------------------------------------
void PsyExerciseBuilding::SetPEBPlains()
{
	int i;

	cam->SetPlains(FLAT_PLAIN, -3000.0, 36000.0, 10450.0, 10450.0, 25250.0, 45610.0, 10250.0, 10550.0); // ENDS AT PsyEx Stairwell

	GLdouble step = 10000.0;
	GLdouble stepLength = 24550.0;

	// Stairs to level 0
	for (i = 0; i < 7; i++)
	{
		cam->SetPlains(FLAT_PLAIN, -1506.0, -844.0, step, step, stepLength, stepLength + 100, step - 450, step + 450);
		step += 64.0;
		stepLength += 100.0;
	}

	cam->SetPlains(FLAT_PLAIN, -1506.0, -844.0, 10000.0, 10000.0, 0.0, 24550.0, 10000, 10300); // Level 0

	step = 10900.0;
	stepLength = 24550.0;

	// Stairs to level 1.5
	for (i = 0; i < 7; i++)
	{
		cam->SetPlains(FLAT_PLAIN, -844.0, -182.0, step, step, stepLength, stepLength + 100);
		step -= 64.0;
		stepLength += 100.0;
	}

	cam->SetPlains(FLAT_PLAIN, -844.0, -182.0, 10898.0, 10898.0, 0.0, 24550.0); // Level 1.5

	// Stairs to level 1
	step = 10900.0;
	stepLength = 24550.0;

	for (i = 0; i < 7; i++)
	{
		cam->SetPlains(FLAT_PLAIN, -1506.0, -844.0, step, step, stepLength, stepLength + 100, step - 450, step + 450);
		step += 64.0;
		stepLength += 100.0;
	}
}

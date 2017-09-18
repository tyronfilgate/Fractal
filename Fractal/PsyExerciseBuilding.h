//  PsyExerciseBuilding.h
//  Header file for the Psychology and Exercise Building class
//	Allows the world to display the Psychology and Exercise Building.
//
//  Tyron Filgate, August 2017
//--------------------------------------------------------------------------------------

#include "texturedPolygons.h"
#include "camera.h"
#include "objModel.h"

/**
* @class PsyExerciseBuilding
* @brief This class handles the methods for drawing and displaying the Psychology and Excercise building.
*
* @author Tyrone Filgate
* @version 01
* @date 16/09/2017
*/

class PsyExerciseBuilding
{
public:

	PsyExerciseBuilding();

	/**
	* @brief Function that sets pointers to Shays classes.
	* @param tp_value - Textured Polygon object pointer.
	* @param Camera - Camera object pointer.
	*/
	void SetContents(TexturedPolygons* tp_value, Camera* cam_value);

	/**
	* @brief Function that draws the psychology and excercise buiding.
	*/
	void DrawPEB();

	/**
	* @brief Function that displays the psychology and excercise buiding.
	*/
	void DisplayPEB();

	/**
	* @brief Function that sets collision for the psychology and excercise buiding.
	*/
	void SetPEBCollision();

	/**
	* @brief Function that sets the plains for the psychology and excercise buiding.
	*/
	void SetPEBPlains();

	/**
	* @brief Returns true if the player is near the entry point to the fractal world.
	* @return bool - Whether or not entry is possible.
	*/
	bool CanEnterFractal();

	/**
	* @brief Displays the entry prompt if the player is within range of it.
	* @param screenWidth - Used to help position prompt horizontally.
	* @param screenWidth - Used to help position prompt vertically.
	*/
	void DisplayEnterPrompt(const int & screenWidth, const int & screenHeight);

private:

	/**
	* @brief Function that draws the psy building doorway.
	*/
	void DrawDoorway();

	/**
	* @brief Function that draws the psy building entace room.
	*/
	void DrawEntranceRoom();

	/**
	* @brief Function that draws the stairs to level 1
	*/
	void DrawStairsDown();

	/**
	* @brief Function that draws the stairs to level 1.5
	*/
	void DrawStairsUp();

	/**
	* @brief Function that draws the stairs to level 0
	*/
	void DrawLevelZero();

	/**
	* @brief Function that draws  level one half.
	*/
	void DrawLevelOneHalf();

	/**
	* @brief Function that draws stairwell.
	*/
	void DrawStairwell();

	/**
	* @brief Function that draws doors and windows.
	*/
	void DrawDoorsandWindows();

	/**
	* @brief Function that draws the stairs to level one.
	*/
	void DrawStairsUpLvl1();

	/**
	* @brief Function that draws the fractal entry prompt.
	*/
	void DrawPrompts();

	/**
	* @brief Function that draws the OBJ models used in the tour.
	*/
	void DrawObjObjects();


	/**
	* @brief Function that displays the psy building doorway.
	*/
	void DisplayDoorway();

	/**
	* @brief Function that displays the psy building entrance room.
	*/
	void DisplayEntranceRoom();

	/**
	* @brief Function that displays the stairs heading down to level 0.
	*/
	void DisplayStairsDown();

	/**
	* @brief Function that displays the stairs heading up to level 1.
	*/
	void DisplayStairsUp();

	/**
	* @brief Function that displays level 0.
	*/
	void DisplayLevelZero();

	/**
	* @brief Function that displays level 1.5.
	*/
	void DisplayLevelOneHalf();

	/**
	* @brief Function that displays the stairwell.
	*/
	void DisplayStairwell();

	/**
	* @brief Function that displays the doors and windows.
	*/
	void DisplayDoorsandWindows();

	/**
	* @brief Function that displays the stairs up to level 1.
	*/
	void DisplayStarsUpLvl1();

	/**
	* @brief Function that displays the various OBJ objects.
	*/
	void DisplayObjObjects();

	///Textured Polygon object from Shay's code.
	TexturedPolygons* tp;
	///Camera object from Shay's code.
	Camera* cam;

	//OBJ model object.
	objModel ob;
};
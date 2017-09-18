//  Fractal.h
//  Header file for the Fractal class
//	The code used for the Fractal Game.
//
//  Tyron Filgate, August 2017
//--------------------------------------------------------------------------------------

#include "texturedPolygons.h"
#include "camera.h"
#include "objModel.h"
#include "world.h"

/**
* @class Fractal
* @brief This class handles the game state and world for fractal.
*
* @author Tyrone Filgate
* @version 01
* @date 16/09/2017
*
* @author Morgan Smolder
* @version 02
* @date 17/09/2017
*/

class Fractal
{
public:

	Fractal();	

	/**
	* @brief Display function used to render the fractal world.
	*/
	void FractalDisplay(); 	

	/**
	* @brief Sets pointers to Shays functions, classes and variables.
	* @param tp_value - Pointer to Shay's Textured Polygon class.
	* @param cam_value - Pointer to Shay's camera class.
	* @param newShayDisplayFunc - Pointer to Shay's display function.
	* @param newfrac - Pointer to Fractal object to be used for switching gamestate.
	* @param newshayFrameCountFunction - Pointer to Shay's frame count function.
	* @param newstepIncrement - Pointer to Shay's step increment variable.
	* @param newangleIncrement - Pointer to Shay's angle increment variable.
	* @param newscreenWidth - Pointer to Shay's screen width variable.
	* @param newscreenHeight - Pointer to Shay's screen height variable.
	*/
	void SetContents(TexturedPolygons* tp_value, Camera* cam_value, void(*newShayDisplayFunc)(),
		Fractal* newfrac, void(*newshayFrameCountFunction)(), GLdouble* newstepIncrement, 
		GLdouble* newangleIncrement, int* newscreenWidth, int* newscreenHeight);
	
	/**
	* @brief Function that handles the various game states, including switching between Shays world and Fractals.
	*/
	static void GameState();

	/**
	* @brief Function that procedurally generates the Fractal World.
	*/
	void InitaliseWorld();

	/**
	* @brief Returns the number of bounding boxes in the encapsulated environment.
	*
	* @return int - The number of bounding boxes.
	*/
	int getNumBoundingBoxes();

	/**
	* @brief Adds bounding boxes to Shay's collision. 
	*
	* @param startBBox - The starting index to begin adding bounding boxes.
	*/
	void setBounds(unsigned startBBox);

	/**
	* @brief Function that initalises the camera position and OpenGl settings for Fractal.
	*/
	void initFractal();

	/**
	* @brief Function that sets a new game state value.
	* @param newstate - The new game state.
	*/
	void setState(int newstate);

	/**
	* @brief Function that returns the game state.
	* @return int - The game state.
	*/
	int getState();

	void DrawPrompts();

private:
	///The game state.
	static int state;
	///Step increment pointer to Shay's code.
	GLdouble* stepIncrement;
	///Angle increment pointer to Shay's code.
	GLdouble* angleIncrement;
	///The width of the screen.
	int* screenWidth;
	///The height of the screen.
	int* screenHeight;
	///Textured Polygon Object.
	TexturedPolygons* tp;
	///Camera object
	Camera* cam;
	///World object
	world w;
	///Pointer to shays display function.
	static void(*shayDisplayFunc)();
	///Pointer to shays frame count function
	static void(*shayFrameCountFunction)();
	///Pointer to a fractal object.
	static Fractal* frac;
	
	/**
	* @brief Function that displays the welcome image.
	*/
	void DisplayWelcome();

	/**
	* @brief Function that displays the game instructions.
	*/
	void DisplayInstructions();

	/**
	* @brief Function that displays the exit image.
	*/
	void DisplayExit();
};
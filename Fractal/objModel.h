#pragma once

#include "objLoader.h"
#include "GL/glut.h"
#include "coords.h"
#include "RGB.h"
#include "BBoxCoords.h"

/**
* @struct TGAFile
* @brief A struct which is used to hold data parsed from a TGA file.
* @author Morgan Smolder
*/
struct TGAFile{
	///The parsed data.
	GLubyte* data;
	///The bit depth of the image.
	unsigned pixelsize;
	///THe width of the image.
	unsigned width;
	///The height of the image.
	unsigned height;
};

/**
* @class objModel
* @brief A class which can be used as a handle for rendering OBJ data.
*
* @author Morgan Smolder
* @version 01
* @date 15/09/2017
*/

class objModel
{
public:
	objModel();
	objModel(std::string filename);

	/**
	* @brief Loads an OBJ file from a given directory.
	*
	* @param filename - The name of the file to load.
	* @return bool - Indicates whether or not the file was loaded successfully.
	*/
	bool loadOBJ(std::string filename);

	/**
	* @brief Creates a display list from OBJ file data.
	*
	* @param listno - The new list number.
	* @param translate - The translation matrix to use when creating the list.
	* @param scale - The scale matrix to use when creating the list.
	* @param rotate - The rotation matrix to use when creating the list.
	* @param rotateamount - The angle at which to rotate the model.
	* @pre OBJ data has already been loaded.
	*/
	void createDisplayList(const int &listno, point3 translate = point3(), point3 scale = point3(), point3 rotate = point3(), float rotateamount = 0);

	/**
	* @brief Creates a wireframe display list from OBJ file data.
	*
	* @param listno - The new list number.
	* @param translate - The translation matrix to use when creating the list.
	* @param scale - The scale matrix to use when creating the list.
	* @param rotate - The rotation matrix to use when creating the list.
	* @param rotateamount - The angle at which to rotate the model.
	* @pre OBJ data has already been loaded.
	*/
	void createWireFrameDisplayList(const int &listno, RGB c, point3 translate = point3(), point3 scale = point3(), point3 rotate = point3(), float rotateamount = 0);

	/**
	* @brief Renders a model from OBJ file data.
	*
	* @param translate - The translation matrix to use when rendering the model.
	* @param scale - The scale matrix to use when rendering the model.
	* @param rotate - The rotation matrix to use when rendering the model.
	* @param rotateamount - The angle at which to rotate the model.
	* @pre OBJ data has already been loaded.
	*/
	void renderModel(point3 translate = point3(), point3 scale = point3(), point3 rotate = point3(), float rotateamount = 0);

	/**
	* @brief Renders a wireframe model from OBJ file data.
	*
	* @param translate - The translation matrix to use when rendering the model.
	* @param scale - The scale matrix to use when rendering the model.
	* @param rotate - The rotation matrix to use when rendering the model.
	* @param rotateamount - The angle at which to rotate the model.
	* @pre OBJ data has already been loaded.
	*/
	void renderWireFrameModel(RGB c, point3 translate = point3(), point3 scale = point3(), point3 rotate = point3(), float rotateamount = 0);
	
	/**
	* @brief Sets the start texture number to use when loading texture data into OpenGL.
	*
	* @param newstart - The start texture number.
	*/
	void setStartTex(unsigned newstart);

	/**
	* @brief Clears the model data.
	*/
	void clear();

	/**
	* @brief Returns the models bounding box information.
	*
	* @return BBoxCoords - The bounding box for the model.
	*/
	const BBoxCoords & getBounds() const;

private:
	///The start texture number. Shared and incremented by all OBJ models.
	static unsigned starttex;
	///The texture IDs for a model.
	std::map<std::string, unsigned> texIDs;
	///Holds OBJ file data.
	objLoader objfile;
	///Contains bounding box information.
	BBoxCoords bounds;

	/**
	* @brief Adds a new texture ID to the texture map.
	*
	* @param newtexture - The new texture ID.
	* @return Returns false if the texture already exists in the map.
	*/
	bool addTextureID(std::string newtexture);

	/**
	* @brief Loads a TGA texture from file.
	*
	* @param texID - The new texture ID.
	* @param filename - The name of the file to load.
	* @return Returns false if the texture is not found or is unsupported.
	*/
	bool loadTGATexture(unsigned& texID, std::string filename);

	/**
	* @brief Loads a TGA texture into OpenGL.
	*
	* @param texID - The texture ID.
	* @param imagedata - The parsed pixel data to give to OpenGL.
	*/
	void createTexture(unsigned& texID, TGAFile imagedata);

	/**
	* @brief Frees the memory occupied by an image.
	*
	* @param imagedata - The data to free.
	*/
	void freeImage(TGAFile imagedata);

	/**
	* @brief Generates a bounding box for the model.
	*/
	void genBounds();

};


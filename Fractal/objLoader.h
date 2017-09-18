#ifndef OBJHANDLE_H
#define OBJHANDLE_H

#include <map>
#include <iostream>
#include "mtlLoader.h"
#include "fileLoader.h"

///Type for holding points of individual faces
typedef std::vector<int> facepoint;

///Type for holding whole faces
typedef std::vector<facepoint> face;

///Type for holding groups of faces.
typedef std::vector<face> facegroup;

/**
* @struct rendergroup
* @brief A struct which is used to hold group data parsed from an OBJ file.
* @author Morgan Smolder
*/
struct rendergroup {
	///The name of the group
	std::string groupname;
	///The material which should be used to render the group.
	std::string material;
	///The vertices in the group.
	std::vector<point> vertices;
	///The texture coordinates in the group.
	std::vector<point2d> texcoords;
	///The normals in the group.
	std::vector<point> normals;
	///The number of faces in the group.
	unsigned numface;
};

/**
* @class objLoader
* @brief A class which loads and encapsulates OBJ data.
*
* @author Morgan Smolder
* @version 01
* @date 15/09/2017
*/

class objLoader : public fileLoader
{
public:
	objLoader();

	/**
	* @brief Loads an OBJ file from a given directory.
	*
	* @param filename - The name of the file to load.
	* @return bool - Indicates whether or not the file was loaded successfully.
	*/
	bool loadFile(std::string filename);

	/**
	* @brief Returns the verticies from a requested group.
	*
	* @param groupno - The group number to load the verticies from.
	* @return std::vector<point> - The verticies from the requested group.
	* @pre Requested index has been parsed and filled with vertex data.
	*/
	const std::vector<point>& getVertices(unsigned groupno = 0) const;

	/**
	* @brief Returns the texture coordinate data from a requested group.
	*
	* @param groupno - The group number to load the texture coordinates from.
	* @return std::vector<point2d> - The texture coordinates from the requested group.
	* @pre Requested index has been parsed and filled with texture coordinate data.
	*/
	const std::vector<point2d>& getTexCoords(unsigned groupno = 0) const;

	/**
	* @brief Returns the normals from a requested group.
	*
	* @param groupno - The group number to load the normals from.
	* @return std::vector<point> - The normals from the requested group.
	* @pre Requested index has been parsed and filled with normal data.
	*/
	const std::vector<point>& getNormals(unsigned groupno = 0) const;

	/**
	* @brief Used to retrieve the material for a given group.
	*
	* @param groupno - The group number to load the material from.
	* @param store - A struct to copy the material data into.
	* @return bool - Returns true if the given group has an associated material, otherwise returns false.
	*/
	bool getMaterial(unsigned groupno, mtlMaterial& store) const;

	/**
	* @brief Returns the number of faces in a given group.
	*
	* @param groupno - The group number to get the number of faces from.
	* @return unsigned - The number of faces in the requested group.
	* @pre Requested index has been parsed and hes face data.
	*/
	unsigned getNumFace(unsigned groupno = 0) const;

	/**
	* @brief Returns the number of groups in the file.
	*
	* @return unsigned - The number of groups in the file.
	*/
	unsigned getNumGroups() const;

	/**
	* @brief Deletes all stored data, freeing memory.
	*/
	void clear();

private:
	///A vector containing the parsed groups.
	std::vector<rendergroup> groups;
	///An accompanying MTL file loader
	mtlLoader mtlfile;
	///Used to keep track of wether or not the OBJ model being loaded has an associated MTL file.
	bool mtlfound;


	/**
	* @brief Parses OBJ data from a given file.
	*
	* @param infile - The file to load the data from.
	* @param tempvert - Holds vertices loaded from the file.
	* @param temptexcord - Holds texture coordinates loaded from the file.
	* @param tempnormals - Holds normals loaded from the file.
	* @param faces - Holds faces loaded from the file.
	* @return bool - Returns whether or not the operation succeeded.
	*/
	bool parseFile(std::ifstream &infile, std::vector<point> &tempvert, std::vector<point2d> &temptexcord, std::vector<point> &tempnormals, std::vector<facegroup> &faces);

	/**
	* @brief Parses face data from a string.
	*
	* @param toparse - The string to parse the data from.
	* @param store - The face to store the data in.
	*/
	static void parseFaces(std::string toparse, face &store);

	/**
	* @brief Sorts the parsed data into groups.
	*
	* @param tempvert - Holds vertices loaded from the file.
	* @param temptexcord - Holds texture coordinates loaded from the file.
	* @param tempnormals - Holds normals loaded from the file.
	* @param faces - Holds faces loaded from the file.
	*/
	void sortData(const std::vector<point> &tempvert, const std::vector<point2d> &temptexcord, const std::vector<point> &tempnormals, const std::vector<facegroup> &faces);

	/**
	* @brief Initalises a new group struct. 
	*
	* @param name - Name of the new group.
	*/
	void createNewGroup(std::string name = "Default");
};

#endif // OBJHANDLE_H

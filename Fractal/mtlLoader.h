#pragma once

#include <map>
#include <iostream>
#include "fileLoader.h"

/**
* @struct mtlMaterial
* @brief A struct which holds material data parsed from an MTL file.
* @author Morgan Smolder
*/
struct mtlMaterial {
	///Material ambient color.
	point Ka;
	///Material diffuse color.
	point Kd;
	///Material specular color.
	point Ks;
	///d value
	float d;
	///Ns value
	float Ns;
	///Matrial illumination level.
	int illum;
	///Ambient texture
	std::string map_Ka;
	///Diffuse texture
	std::string map_Kd;
	///Specular texture
	std::string map_Ks;
	///d texture
	std::string map_d;
	///Ns texture
	std::string map_Ns;
	///Bump map
	std::string map_bump;
};

/**
* @class mtlLoader
* @brief A class which loads and encapsulates MTL data.
*
* @author Morgan Smolder
* @version 01
* @date 15/09/2017
*/

class mtlLoader : public fileLoader
{
public:
	mtlLoader();

	/**
	* @brief Loads an MTL file from a given directory.
	*
	* @param filename - The name of the file to load.
	* @return bool - Indicates whether or not the file was loaded successfully.
	*/
	bool loadFile(std::string filename);

	/**
	* @brief Returns the material file stored at a specified index in the material map.
	*
	* @param materialkey - The material key to be loaded.
	* @return mtlMaterial - The requested material.
	*/
	const mtlMaterial & getMaterial(std::string materialkey) const;

	/**
	* @brief Checks whether a given material exists in the material map.
	*
	* @param materialkey - The material key to be loaded.
	* @return mtlMaterial - The requested material.
	*/
	bool hasMaterial(std::string materialKey) const;

	/**
	* @brief Clears the material map, freeing memory.
	*/
	void clear();

private:
	///A map containing the parsed material data.
	std::map<std::string, mtlMaterial> materials;

	/**
	* @brief Parses MTL data from a given file.
	*
	* @param infile - The file to load the data from.
	* @return bool - Returns whether or not the operation succeeded.
	*/
	bool parseFile(std::ifstream &infile);
};


#include "fileLoader.h"

void fileLoader::parseString(std::string toparse, std::string &store) {
	toparse = toparse.substr(toparse.find(' ') + 1);
	store = toparse;
}

void fileLoader::parseCoOrdsXYZ(std::string toparse, point &store) {
	toparse = toparse.substr(toparse.find(' ') + 1);

	store.x = atof(toparse.substr(0, toparse.find(' ')).c_str());
	toparse = toparse.substr(toparse.find(' ') + 1);

	store.y = atof(toparse.substr(0, toparse.find(' ')).c_str());
	toparse = toparse.substr(toparse.find(' ') + 1);

	store.z = atof(toparse.substr(0, toparse.find('\n')).c_str());
}

void fileLoader::parseCoOrdsXY(std::string toparse, point2d &store) {
	toparse = toparse.substr(toparse.find(' ') + 1);

	store.x = atof(toparse.substr(0, toparse.find(' ')).c_str());
	toparse = toparse.substr(toparse.find(' ') + 1);

	store.y = atof(toparse.substr(0, toparse.find('\n')).c_str());
}

void fileLoader::cleanLine(std::string &line){
	while (line.at(0) == ' ') {
		line = line.substr(1);
	}

	while (line.find("  ") != std::string::npos) {
		line = line.substr(0, line.find("  ")) + line.substr(line.find("  ") + 1);
	}

	//Remove Tabs
	while (line.find("	") != std::string::npos){
		line = line.substr(0, line.find("	")) + line.substr(line.find("	") + 1);
	}

	if (line.find('#')) {
		line = line.substr(0, line.find('#'));
	}

	if (line.at(line.size() - 1) == ' ') {
		line.substr(0, line.size() - 1);
	}
}
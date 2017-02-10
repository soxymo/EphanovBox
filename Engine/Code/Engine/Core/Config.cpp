#include "Engine/Core/Config.hpp"
#include <fstream>
#include <map>
#include <iostream>
#include <string>

using namespace std;


bool Config::ConfigSystemStartup(std::string config_file) {
	std::string line;
	ifstream configFile;
	configFile.open(config_file);
	if (configFile.is_open()) {
		while (std::getline(configFile, line) ){
			int splitterIndex = line.find_first_of(SEPARATOR);

			if (splitterIndex > 0) {
				configMap[line.substr(0, splitterIndex)] = line.substr(splitterIndex + 1, line.length());
			}
		}
	}

	configFile.close();
	return true;
}

bool Config::ConfigGetInt(int *outv, std::string id) {
	if (configMap.find(id) == configMap.end()) {
		return false;
	}
	*outv = atoi(configMap[id].c_str());
	return true;
}

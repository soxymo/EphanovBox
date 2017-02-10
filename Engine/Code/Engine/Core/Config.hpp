#pragma once
#include <iostream>
#include <string.h>
#include <map>
#include <iostream>
#include <string>

const char SEPARATOR = '=';


class Config {
public:
	bool ConfigSystemStartup(std::string config_file);
	void ConfigSystemShutdown();

	// Setters - feel free to use std::string
	void ConfigSet(std::string name, std::string value);
	void ConfigSet(std::string name, int const value);
	void ConfigSet(std::string name, float const value);
	void ConfigSet(std::string name, bool const value);

	// Easy check for simple on/off flags. 
	bool IsConfigSet(std::string id);
	void ConfigUnset(std::string id);

	// Fetching.  If a config exists and is 
	// convertible to the desried type, 
	// place its converted value in the out variable,
	// and return true;
	// Otherwise, return false.
	bool ConfigGetString(char const** outv, std::string id);
	bool ConfigGetBool(bool *outv, std::string id);
	bool ConfigGetInt(int *outv, std::string id);
	bool ConfigGetFloat(float *outv, std::string id);

	// [DEBUG FEATURE] List all currently existing configs.
	void ConfigList();

	
	// Load a config file
	// see sample.config 
	bool ConfigLoadFile(std::string filename);	

private:
	std::map<std::string, std::string> configMap;
}; 
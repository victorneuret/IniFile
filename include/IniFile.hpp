#pragma once

#include <string>
#include <map>

#include "IniParser.hpp"

class IniFile {
public:
	explicit IniFile(std::string fileName);
	std::map<std::string, std::map<std::string, std::string>> getMap();
	int getInt(std::string section, std::string key);
	bool getBool(std::string section, std::string key);

private:
	std::map<std::string, std::map<std::string, std::string>> fileMap;
};

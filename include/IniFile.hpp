#pragma once

#include <string>
#include <map>

#include "IniParser.hpp"

typedef std::map<std::string, std::map<std::string, std::string>> IniMap;

class IniFile {
public:
	explicit IniFile(std::string &fileName);
	const std::map<std::string, std::map<std::string, std::string>>
		&getMap();
	int getInt(std::string section, std::string key);
	bool getBool(std::string section, std::string key);
	void printMap();

private:
	std::map<std::string, std::map<std::string, std::string>> fileMap;
};

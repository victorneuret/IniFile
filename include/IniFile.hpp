#pragma once

#include <string>
#include <map>

#include "IniParser.hpp"

class IniFile {
public:
	explicit IniFile(std::string fileName);
	int getInt(std::string sectionName, std::string key);
	std::string getString(std::string sectionName, std::string key);

private:
	std::map<std::string, std::map<std::string, std::string>> fileMap;
};




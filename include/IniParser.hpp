#pragma once

#include <string>
#include <map>
#include <fstream>

class IniParser {
public:
	IniParser(std::string &filePath);
	void parse();
	std::string getNextLine();

private:
	std::map<std::string, std::map<std::string, std::string>> fileMap;
	std::fstream file;
};




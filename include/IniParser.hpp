#pragma once

#include <string>
#include <map>
#include <fstream>

class IniParser {
public:
	IniParser(std::string &filePath);
	void parse();

private:
	std::map<std::string, std::map<std::string, std::string>> fileMap;
	std::fstream file;
	std::string line;
	std::string section = "global";
	std::string key;
	std::string value;

	bool getNextLine();
	void getKey();
	void getValue();
	bool getSection();
};

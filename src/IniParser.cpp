#include <iostream>
#include <string>

#include "IniParser.hpp"

IniParser::IniParser(std::string &filePath)
{
	file.open(filePath, std::fstream::in);
	if (!file.is_open())
		throw std::runtime_error("can't open file: " + filePath);
	parse();
}

void IniParser::parse()
{
	while (getNextLine()) {
		if (getSection())
			continue;
		formatLine();
		getKey();
		getValue();
		fileMap[section][key] = value;
	}
}

void IniParser::printMap()
{
	for (auto sectionElem : fileMap) {
		std::cout << "[" << sectionElem.first << "]" << std::endl;
		for (auto keyElem : fileMap[sectionElem.first])
			std::cout << keyElem.first << ": "
				<< keyElem.second << std::endl;
	}
}

bool IniParser::getNextLine()
{
	if (!std::getline(file, line))
		return false;
	return true;
}

void IniParser::formatLine()
{
	int i = 0;

	while (line[i] != '=') {
		if (line[i] == ' ') {
			line.erase(i, 1);
			continue;
		}
		i++;
	}
	i++;
	while (line[i] == ' ')
		line.erase(i, 1);
}

void IniParser::getKey()
{
	key = line.substr(0, line.find("="));
}

void IniParser::getValue()
{
	value = line.substr(line.find("=") + 1);
}

bool IniParser::getSection()
{
	if (line[0] == '[' && line[line.length() - 1] == ']') {
		section = line.substr(1, line.length() - 2);
		return true;
	}
	return false;
}

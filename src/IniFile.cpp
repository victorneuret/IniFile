#include <string>
#include <iostream>

#include "IniFile.hpp"

IniFile::IniFile(std::string fileName)
{
	IniParser parser(fileName);
	fileMap = parser.getMap();
}

void IniFile::printMap()
{
	for (auto sectionElem : fileMap) {
		std::cout << "[" << sectionElem.first << "]" << std::endl;
		for (auto keyElem : fileMap[sectionElem.first])
			std::cout << keyElem.first << ": "
				<< keyElem.second << std::endl;
	}
}

std::map<std::string, std::map<std::string, std::string>> IniFile::getMap()
{
	return fileMap;
}

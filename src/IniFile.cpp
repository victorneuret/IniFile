#include <string>
#include <iostream>

#include "IniFile.hpp"

IniFile::IniFile(std::string &fileName)
{
	try {
		IniParser parser(fileName);
		fileMap = parser.getMap();
	} catch (std::runtime_error &str) {
		std::cerr << str.what() << std::endl;
	}
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

const std::map<std::string, std::map<std::string, std::string>>
	&IniFile::getMap()
{
	return fileMap;
}

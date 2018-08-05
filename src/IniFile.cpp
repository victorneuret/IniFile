#include <string>
#include <iostream>

#include "IniFile.hpp"

IniFile::IniFile(std::string fileName)
{
	IniParser parser(fileName);
	parser.printMap();
}

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
	std::string str = getNextLine();

	while (!str.empty()) {
		std::cout << str << std::endl;
		str = getNextLine();
	}
}

std::string IniParser::getNextLine()
{
	std::string line;

	if (!std::getline(file, line))
		return "";
	return line;
}

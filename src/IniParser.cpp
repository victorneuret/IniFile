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

std::map<std::string, std::map<std::string, std::string>> IniParser::getMap()
{
	return fileMap;
}

void IniParser::parse()
{
	while (getNextLine()) {
		if (getSection() || isCommentLine())
			continue;
		formatLine();
		getKey();
		getValue();
		fileMap[section][key] = value;
	}
}

bool IniParser::getNextLine()
{
	if (!std::getline(file, line))
		return false;
	return true;
}

bool IniParser::isCommentLine()
{
	if (line[0] == ';' || line[0] == '#')
		return true;
	for (int i = 0; line[i]; i++) {
		if ((line[i] == ';' || line[i] == '#') && line[i - 1] != '\\')
			line.erase(i, line.length() - 1);
	}
	return false;
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
	for (int j = line.length() - 1; line[j] == ' '; j--)
		line.erase(j, 1);
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

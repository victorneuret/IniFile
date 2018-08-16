#include <iostream>
#include <string>

#include "IniParser.hpp"
#include "EscapeChar.hpp"

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
		std::cout << '1' << std::endl;
		formatLine();
		escapeCharacter();
		getKey();
		getValue();
		valueQuotes();
		fileMap[section][key] = value;
	}
}

bool IniParser::getNextLine()
{
	if (!std::getline(file, line))
		return false;
	actualLine++;
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

	while (line[i] != '=' && line[i] != ':') {
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
	size_t equalPos = line.find_first_of('=');
	size_t colonPos = line.find_first_of(':');
	
	if (colonPos == std::string::npos && equalPos == std::string::npos)
		throw std::runtime_error(
			MISSING_SEPARATOR + std::to_string(actualLine));
	if (colonPos == std::string::npos || equalPos < colonPos)
		key = line.substr(0, line.find("="));
	else if (equalPos == std::string::npos || equalPos > colonPos)
		key = line.substr(0, line.find(":"));	
	std::cout << line << std::endl;
}

void IniParser::getValue()
{
	size_t equalPos = line.find_first_of('=');
	size_t colonPos = line.find_first_of(':');
	
	if (colonPos == std::string::npos && equalPos == std::string::npos)
		throw std::runtime_error(
			MISSING_SEPARATOR + std::to_string(actualLine));
	if (colonPos == std::string::npos || equalPos < colonPos)
		value = line.substr(line.find("=") + 1);
	else if (equalPos == std::string::npos || equalPos > colonPos)
		value = line.substr(line.find(":") + 1);
	std::cout << line << std::endl;
}

bool IniParser::getSection()
{
	if (line[0] == '[' && line[line.length() - 1] == ']') {
		section = line.substr(1, line.length() - 2);
		return true;
	}
	return false;
}

void IniParser::valueQuotes()
{
	int nbQuotes = 0;
	int length = value.length() - 1;

	for (int i = 0; value[i]; i++)
		if ((value[i] == '"' || value[i] == '\''))
			// && ((i > 1) ? value[i - 1] != '\\' : 1))
			nbQuotes++;
	if ((nbQuotes != 2 && nbQuotes != 0) 
		|| (nbQuotes == 2 && value[0] != value[length]))
		throw std::runtime_error(
			INVALID_QUOTES + std::to_string(actualLine));
	else if (nbQuotes == 2) {
		value.erase(0, 1);
		value.erase(value.length() - 1, 1);
	}
}

void IniParser::escapeCharacter()
{
	EscapeChar escape(line);
	line = escape.getString();
}
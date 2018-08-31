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
		formatLine();
		getKey();
		getValue();
		valueQuotes();
		escapeCharacter();
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

	while (line[i]) {
		if ((line[i] == '=' && line[i - 1] != '\\')
			|| (line[i] == ':' && line[i - 1] != '\\'))
			break;
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
	size_t i = 1;

	while (line[i++])
		if ((line[i] == '=' && line[i - 1] != '\\')
			|| (line[i] == ':' && line[i - 1] != '\\'))
			break;
	if (i >= line.length())
		throw std::runtime_error(
			MISSING_SEPARATOR + std::to_string(actualLine));
	key = line.substr(0, i);
}

void IniParser::getValue()
{
	size_t i = 1;

	while (line[i++])
		if ((line[i] == '=' && line[i - 1] != '\\')
			|| (line[i] == ':' && line[i - 1] != '\\'))
			break;
	if (i >= line.length())
		throw std::runtime_error(
			MISSING_SEPARATOR + std::to_string(actualLine));
	value = line.substr(i + 1);
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
		if ((value[i] == '"' && (i > 0 ? value[i - 1] != '\\' : 1))
			|| (value[i] == '\'' && (i > 0 ? value[i - 1] != '\\' : 1)))
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
	EscapeChar escape(key);
	key = escape.getString();
	escape.setString(value);
	escape.replace();
	value = escape.getString();
}
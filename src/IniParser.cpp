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
		if (isBlankLine() || getSection() || isCommentLine())
			continue;
		formatLine();
		getKey();
		getValue();
		valueQuotes();
		escapeCharacter();
		callKey();
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

bool IniParser::isBlankLine()
{
	int nbChar = 0;
	bool blankLine = false;

	for (int i = 0; line[i]; i++)
		if (line[i] != ' ' && line[i] != '\t')
			nbChar++;
	if (nbChar == 0)
		blankLine = true;
	return blankLine;
}

bool IniParser::isCommentLine()
{
	while (line[0] == ' ' || line[0] == '\t')
		line.erase(0, 1);
	if (line[0] == ';' || line[0] == '#') {
		line = "";
		return true;
	}
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
	while (line[i] == ' ' || line[i] == '\t')
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
	lineBreak();
}

void IniParser::lineBreak()
{
	if (value[value.length() - 1] == '\\') {
		value.erase(value.length() - 1, 1);
		while (value[value.length() - 1] == ' '
			|| value[value.length() - 1] == '\t')
			value.erase(value.length() - 1, 1);
		value.append(" ");
		getNextLine();
		if (isCommentLine()) {
			value.append("\\");
			lineBreak();
		}
		while (line[0] == ' ' || line[0] == '\t')
			line.erase(0, 1);
		while (line[line.length() - 1] == ' '
			|| line[line.length() - 1] == '\t')
			line.erase(line.length() - 1, 1);
		value.append(line);
	}
	if (value[value.length() - 1] == '\\')
		lineBreak();
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
			|| (value[i] == '\''
			&& (i > 0 ? value[i - 1] != '\\' : 1)))
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

void IniParser::callKey()
{
	std::string replaceKey;

	for (int i = 0; value[i]; i++) {
		if (value[i] == '$') {
			replaceKey = parseKey(i);
			replaceCalledKey(i, replaceKey);
		}
	}
}

std::string IniParser::parseKey(int pos)
{
	int endPos = 0;
	std::string replaceKey;

	if (value[pos + 1] == '\0' || value[pos + 1] != '{')
		return "";
	for (int i = 0; value[i]; i++) {
		if (value[i] == '}') {
			endPos = i;
			break;
		}
	}
	if (endPos == 0)
		return "";
	pos += 2;
	replaceKey = value.substr(pos, endPos - pos);
	return replaceKey;
}

void IniParser::replaceCalledKey(int pos, std::string replaceKey)
{
	int endPos = 0;

	if (replaceKey == "")
		return;
	for (int i = pos; value[i]; i++)
		if (value[i] == '}') {
			endPos = i;
			break;
		}
	if (fileMap[section].count(replaceKey) > 0)
		value.replace(pos, endPos + 1 - pos,
			fileMap[section][replaceKey]);
	else
		throw std::runtime_error(
			UNKNOW_KEY + std::to_string(actualLine));
}

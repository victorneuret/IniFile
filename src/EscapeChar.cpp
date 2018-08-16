#include <string>
#include <iostream>

#include "EscapeChar.hpp"

EscapeChar::EscapeChar(std::string str)
{
	setString(str);
	replace();
}

void EscapeChar::setString(std::string str)
{
	string = str;
}

std::string EscapeChar::getString()
{
	return string;
}

void EscapeChar::replace()
{
	for (int i = 0; string[i]; i++) {
		if (isEscapeChar(i))
			replaceThis(i);
	}
}

bool EscapeChar::isEscapeChar(int i)
{
	if (string[i] != '\\' || string[i + 1] == '\0')
		return false;
	for (int j = 0; escapeCharList[j][0] != '\0'; j++)
		if (string[i + 1] == escapeCharList[j][0]) {
			replaceTo = escapeCharList[j][1];
			return true;
		}
	replaceTo = '\0';
	return false;
}

void EscapeChar::replaceThis(int i)
{	
	string.insert(i, 1, replaceTo);
	string.erase(i + 1, 2);
}

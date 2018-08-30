#pragma once

#include <string>

class EscapeChar {
public:
	EscapeChar(std::string str);
	std::string getString();
	void setString(std::string str);
	void replace();

private:
	std::string string;
	char replaceTo = '\0';
    char escapeCharList[15][2] = {
		{'\\', '\\'},
		{'0', '\0'},
		{'a', '\a'},
		{'b', '\b'},
		{'t', '\t'},
		{'r', '\r'},
		{'n', '\n'},
		{';', ';'},
		{'#', '#'},
		{'=', '='},
		{':', ':'},
		{'x', 'x'},
		{'"', '"'},
		{'\'', '\''},
		{'\0', '\0'}
	};

	bool isEscapeChar(int i);
	void replaceThis(int i);
};
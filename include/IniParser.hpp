#pragma once

#include <string>
#include <map>
#include <fstream>

#define INVALID_QUOTES "Invalid quotes on line "
#define MISSING_SEPARATOR "Missing separator on line "
#define UNKNOW_KEY "The key asked in unknow at line "
#define BAD_SYNTAX "Bas syntax at line "

class IniParser
{
  public:
	IniParser(std::string &filePath);
	void parse();
	const std::map<std::string, std::map<std::string, std::string>>
		&getMap();

  private:
	std::map<std::string, std::map<std::string, std::string>> fileMap;
	std::fstream file;
	std::string line;
	std::string section = "global";
	std::string key;
	std::string value;
	int actualLine = 0;

	bool getNextLine();
	void getKey();
	void getValue();
	void lineBreak();
	bool getSection();
	bool isCommentLine();
	bool isBlankLine();
	void formatLine();
	void valueQuotes();
	void escapeCharacter();
	void callKey();
	std::string parseKey(int pos);
	void replaceCalledKey(int pos, std::string replaceKey);
};

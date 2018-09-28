#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(lineBreak, simpleLineBreak)
{
	std::string fileName = "testSimpleLineBreak.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "name = John\\" << std::endl;
    testFile << "Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
    cr_assert_eq(map["global"].size(), 1);
	cr_assert_eq(map["global"]["name"], "John Doe");
	remove(fileName.c_str());
}

Test(lineBreak, spacesLineBreak)
{
	std::string fileName = "testSpacesLineBreak.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "name = John      \\" << std::endl;
    testFile << "           Doe       " << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
    cr_assert_eq(map["global"].size(), 1);
	cr_assert_eq(map["global"]["name"], "John Doe");
	remove(fileName.c_str());
}

Test(lineBreak, tabsLineBreak)
{
	std::string fileName = "testTabsLineBreak.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "name = John\t\\" << std::endl;
    testFile << "\t\tDoe\t" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
    cr_assert_eq(map["global"].size(), 1);
	cr_assert_eq(map["global"]["name"], "John Doe");
	remove(fileName.c_str());
}

Test(lineBreak, lineBreakKey)
{
	std::string fileName = "testLineBreakKey.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "name = John \\" << std::endl;
    testFile << "lastName = Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
    cr_assert_eq(map["global"].size(), 1);
	cr_assert_eq(map["global"]["name"], "John lasteName = Doe");
	remove(fileName.c_str());
}

Test(lineBreak, multipleLineBreak)
{
	std::string fileName = "testMultipleLineBreak.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "name = John \\" << std::endl;
    testFile << "       Doe \\" << std::endl;
    testFile << "       is  \\" << std::endl;
    testFile << "       John" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
    cr_assert_eq(map["global"].size(), 1);
	cr_assert_eq(map["global"]["name"], "John Doe is John");
	remove(fileName.c_str());
}
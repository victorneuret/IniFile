#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(key, key)
{
	std::string fileName = "testKey.ini";
	std::ofstream testFile(fileName);
	IniMap map;

	testFile << "name = John" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"].count("name"), 1);
	remove(fileName.c_str());
}

Test(key, spaceInKeyName)
{
	std::string fileName = "testSpaceInKeyName.ini";
	std::ofstream testFile(fileName);
	IniMap map;

	testFile << "first name = John" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"].count("first name"), 0);
	cr_assert_eq(map["global"].count("firstname"), 1);
	cr_assert_eq(map["global"]["firstname"], "John");
	remove(fileName.c_str());
}

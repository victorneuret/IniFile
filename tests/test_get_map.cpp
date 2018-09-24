#include <iostream>
#include <fstream>
#include <map>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"

#include "tests.hpp"

Test(getMap, getEmptyMap)
{
	std::string fileName = "testGetEmptyMap.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map.size(), 0);
	remove(fileName.c_str());
}

Test(getMap, GetSimpleMap)
{
	std::string fileName = "testGetSimpleMap.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "name = John" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map.size(), 1);
	remove(fileName.c_str());
}

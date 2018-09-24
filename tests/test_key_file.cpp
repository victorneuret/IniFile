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
	std::ofstream testFile(fileName, std::fstream::out | std::fstream::trunc);
	MAP_DEFINITION map;

	testFile << "name = John" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"].count("name"), 1);
	remove(fileName.c_str());
}

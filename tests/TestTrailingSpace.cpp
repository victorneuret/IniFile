#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(trailingSpace, trailingSpace)
{
	std::string fileName = "testTrailingSpace.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "     firstName           =          John    " << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"]["firstName"], "John");
	remove(fileName.c_str());
}

Test(trailingSpace, noSpace)
{
	std::string fileName = "testNoSpace.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "lastName=Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"]["lastName"], "Doe");
	remove(fileName.c_str());
}

#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(blankLine, blankLine)
{
	std::string fileName = "testBlankLine.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "[Section]" << std::endl << std::endl;
	testFile << "firstName = John" << std::endl << std::endl << std::endl;
	testFile << "lastName = Doe" << std::endl << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map.count("Section"), 1);
	cr_assert_eq(map["Section"].size(), 2);
	cr_assert_eq(map["Section"]["firstName"], "John");
	cr_assert_eq(map["Section"]["lastName"], "Doe");
	remove(fileName.c_str());
}

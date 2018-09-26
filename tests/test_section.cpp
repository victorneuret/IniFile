#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(section, section)
{
	std::string fileName = "testSection.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "[Section]" << std::endl;
	testFile << "firstName = John" << std::endl;
	testFile << "LastName = Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map.count("Section"), 1);
	cr_assert_eq(map["Section"].size(), 2);
	remove(fileName.c_str());
}

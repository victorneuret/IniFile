#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(duplicateKeys, duplicateKeys)
{
	std::string fileName = "testDuplicateKeys.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "name = John Doe" << std::endl;
	testFile << "[Section]" << std::endl;
	testFile << "name = John" << std::endl;
	testFile << "name = Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"]["name"], "John Doe");
	cr_assert_eq(map["Section"].size(), 1);
	cr_assert_eq(map["Section"]["name"], "Doe");
	remove(fileName.c_str());
}

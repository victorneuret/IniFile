#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(keySensitive, keySensitive)
{
	std::string fileName = "testKeySensitive.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "firstName = John" << std::endl;
	testFile << "lastName = Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"]["firstName"], "John");
	cr_assert_eq(map["global"]["lastName"], "Doe");
	remove(fileName.c_str());
}

#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(value, value)
{
	std::string fileName = "testValue.ini";
	std::ofstream testFile(fileName);
	IniMap map;

	testFile << "firstName = John" << std::endl;
	testFile << "age = 42" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"]["firstName"], "John");
	cr_assert_eq(map["global"]["age"], "42");
	remove(fileName.c_str());
}

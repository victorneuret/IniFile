#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(callKey, callKeyBefore)
{
	std::string fileName = "testCallKeyBefore.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "firstName = John" << std::endl;
	testFile << "name = ${firstName}" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"]["firstName"], "John");
	cr_assert_eq(map["global"]["name"], "John");
	remove(fileName.c_str());
}

Test(callKey, callKeyAfter)
{
	std::string fileName = "testCallKeyAfter.ini";
	std::ofstream testFile(fileName);
	MAP_DEFINITION map;

	testFile << "name = ${firstName}" << std::endl;
	testFile << "firstName = John" << std::endl;
	cr_assert_throw(IniParser parser(fileName), std::runtime_error);
	remove(fileName.c_str());
}

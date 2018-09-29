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
	IniMap map;

	testFile << "[Section]" << std::endl;
	testFile << "firstName = John" << std::endl;
	testFile << "lastName = Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map.count("Section"), 1);
	cr_assert_eq(map["Section"].size(), 2);
	remove(fileName.c_str());
}

Test(section, multipleSection)
{
	std::string fileName = "testMultipleSection.ini";
	std::ofstream testFile(fileName);
	IniMap map;

	testFile << "[Section]" << std::endl;
	testFile << "firstName = John" << std::endl;
	testFile << "lastName = Doe" << std::endl;
	testFile << "[Section2]" << std::endl;
	testFile << "age = 42" << std::endl;
	testFile << "fruit = Banana" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map.count("Section"), 1);
	cr_assert_eq(map["Section"].size(), 2);
	cr_assert_eq(map.count("Section2"), 1);
	cr_assert_eq(map["Section2"].size(), 2);
	remove(fileName.c_str());
}

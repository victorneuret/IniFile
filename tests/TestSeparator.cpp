#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(separator, separatorEqual)
{
	std::string fileName = "testSeparatorEqual.ini";
	std::ofstream testFile(fileName);
	IniMap map;

	testFile << "firstName = John" << std::endl;
	testFile << "lastName = Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"]["firstName"], "John");
	cr_assert_eq(map["global"]["lastName"], "Doe");
	remove(fileName.c_str());
}

Test(separator, separatorColon)
{
	std::string fileName = "testSeparatorColon.ini";
	std::ofstream testFile(fileName);
	IniMap map;

	testFile << "firstName : John" << std::endl;
	testFile << "lastName : Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"]["firstName"], "John");
	cr_assert_eq(map["global"]["lastName"], "Doe");
	remove(fileName.c_str());
}

Test(separator, separatorBoth)
{
	std::string fileName = "testSeparatorBoth.ini";
	std::ofstream testFile(fileName);
	IniMap map;

	testFile << "firstName = John" << std::endl;
	testFile << "lastName : Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
	cr_assert_eq(map["global"]["firstName"], "John");
	cr_assert_eq(map["global"]["lastName"], "Doe");
	remove(fileName.c_str());
}

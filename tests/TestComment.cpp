#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>

#include <criterion/criterion.h>

#include "IniParser.hpp"
#include "tests.hpp"

Test(comment, lineCommentOne)
{
	std::string fileName = "testLineCommentOne.ini";
	std::ofstream testFile(fileName);
	IniMap map;

    testFile << "# first line comment" << std::endl;
	testFile << "firstName = John" << std::endl;
	testFile << "# This comment is awesome!" << std::endl;
    testFile << "lastName = Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
    cr_assert_eq(map.count("global"), 1);
	cr_assert_eq(map["global"].size(), 2);
	cr_assert_eq(map["global"]["firstName"], "John");
	cr_assert_eq(map["global"]["lastName"], "Doe");
	remove(fileName.c_str());
}

Test(comment, lineCommentTwo)
{
	std::string fileName = "testLineCommentTwo.ini";
	std::ofstream testFile(fileName);
	IniMap map;

    testFile << "; first line comment" << std::endl;
	testFile << "firstName = John" << std::endl;
	testFile << "; This comment is awesome!" << std::endl;
    testFile << "lastName = Doe" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
    cr_assert_eq(map.count("global"), 1);
	cr_assert_eq(map["global"].size(), 2);
	cr_assert_eq(map["global"]["firstName"], "John");
	cr_assert_eq(map["global"]["lastName"], "Doe");
	remove(fileName.c_str());
}

Test(comment, inlineCommentOne)
{
	std::string fileName = "testInlineCommentOne.ini";
	std::ofstream testFile(fileName);
	IniMap map;

    testFile << "firstName = John #Doe" << std::endl;
	testFile << "# This comment is awesome!" << std::endl;
    testFile << "lastName = Doe      #    Comment" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
    cr_assert_eq(map.count("global"), 1);
	cr_assert_eq(map["global"].size(), 2);
	cr_assert_eq(map["global"]["firstName"], "John");
	cr_assert_eq(map["global"]["lastName"], "Doe");
	remove(fileName.c_str());
}

Test(comment, inlineCommentTwo)
{
	std::string fileName = "testInlineCommentTwo.ini";
	std::ofstream testFile(fileName);
	IniMap map;

    testFile << "firstName = John ;Doe" << std::endl;
	testFile << "# This comment is awesome!" << std::endl;
    testFile << "lastName = Doe      ;    Comment" << std::endl;
	IniParser parser(fileName);
	map = parser.getMap();
    cr_assert_eq(map.count("global"), 1);
	cr_assert_eq(map["global"].size(), 2);
	cr_assert_eq(map["global"]["firstName"], "John");
	cr_assert_eq(map["global"]["lastName"], "Doe");
	remove(fileName.c_str());
}

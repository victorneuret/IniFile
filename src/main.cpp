#include <iostream>
#include <string>

#include "IniFile.hpp"


int main(__attribute__((unused)) int ac, char **av)
{
	std::string str = av[1];
	IniFile iniFile(str);
	iniFile.printMap();
	return 0;
}

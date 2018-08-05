#include <iostream>

#include "IniFile.hpp"


int main(__attribute__((unused)) int ac, char **av)
{
	IniFile iniFile(av[1]);
	iniFile.printMap();
	return 0;
}
